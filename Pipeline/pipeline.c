#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pipeline.h"

int32_t fileOpenStatus = 0;

Data *data;
Reg_File reg;
uint32_t currIndex = 0;

void createPipeline(Stage **head, Stage **tail)
{
	int32_t i;

	data = (Data*) malloc(NUM_STAGES * sizeof(Data));
	
	for (i = 0; i < NUM_STAGES; i++)
	{
		Stage *stagePtr = (Stage*) malloc(sizeof(Stage));

#ifdef DEBUG		
		printf("Stage Address: 0x%x, Data Address[%d]:0x%x\n\r", (unsigned int)stagePtr, i, &data[i]);
#endif		
		stagePtr->id = IF + i;
		stagePtr->next = NULL;
		
		if(*head == NULL)
		{
			*head = stagePtr;
			*tail = stagePtr;
		}
		else
		{
			(*tail)->next = stagePtr;
			*tail = (*tail)->next;
		}

		data[i].isInitialized = false;
		data[i].stageID = -10;
	}
}

void processStage(Stage *stage)
{
	
#ifdef DEBUG		
				printf("currIndex:%d\n\r", currIndex);
#endif
	
	switch(stage->id)
	{
		case IF: 		
				if (currIndex >= IF)
				{
#ifdef DEBUG 
					printf("*********************************************\n\r");
					printf("Stage IF\n\r");
					printf("*********************************************\n\r");				
					printf("data array Index: %d , Address:0x%x\n\r", (currIndex % NUM_STAGES) - IF, &data[(currIndex % NUM_STAGES) - IF]);
#endif
					data[(currIndex % NUM_STAGES) - IF].stageID = IF;
					stage->data = &data[(currIndex % NUM_STAGES) - IF];
					stage->func = fetch;
					stage->func(stage);
				}
				
				break;
				
		case ID: 		
				if (currIndex >= ID)
				{
#ifdef DEBUG					
					printf("*********************************************\n\r");
					printf("Stage ID\n\r");
					printf("*********************************************\n\r");
					printf("data array Index: %d , Address:0x%x\n\r", (currIndex % NUM_STAGES) - ID, &data[(currIndex % NUM_STAGES) - ID]);
#endif
					data[(currIndex % NUM_STAGES) - ID].stageID = ID;
					stage->data = &data[(currIndex % NUM_STAGES) - ID];
					stage->func = decode;
					stage->func(stage);
				}
				
				break;

		case EXE:  		
				if (currIndex >= EXE)
				{
#ifdef DEBUG
					printf("*********************************************\n\r");
					printf("Stage: EXE\n\r");
					printf("*********************************************\n\r");
					printf("data Index: %d \n\r", (currIndex % NUM_STAGES) - EXE);
#endif
					data[(currIndex % NUM_STAGES) - EXE].stageID = EXE;
					stage->data = &data[(currIndex % NUM_STAGES) - EXE];
					stage->func = execute;
					stage->func(stage);
				}
				
				break;
				
		case MEM:  		
				if (currIndex >= MEM)
				{
#ifdef DEBUG
					printf("*********************************************\n\r");
					printf("Stage: MEM\n\r"); 
					printf("*********************************************\n\r");
					printf("data Index: %d \n\r", (currIndex % NUM_STAGES) - MEM);
#endif
					data[(currIndex % NUM_STAGES) - MEM].stageID = MEM;
					stage->data = &data[(currIndex % NUM_STAGES) - MEM];
					stage->func(stage);
				}	
				
				break;
				
		case WB:  		
				if (currIndex >= WB)
				{
#ifdef DEBUG
					printf("*********************************************\n\r");
					printf("Stage: WB\n\r");
					printf("*********************************************\n\r");
					printf("data Index: %d \n\r", (currIndex % NUM_STAGES) - WB);
#endif			
					data[(currIndex % NUM_STAGES) - WB].stageID = WB;
					stage->data = &data[(currIndex % NUM_STAGES) - WB];
					stage->func(stage);
				}
				
				break;
		
	}
	
	printf("*************************************************\n\r");
}


void fetch(Stage* stage)
{
	static uint8_t fileOpenStatus = 0;
	static FILE *fptr = NULL;
	
	uint32_t getInstr;
	
	printf("Fetch Instruction\n\r");
	
    if (!fileOpenStatus) fptr = fopen("traces.txt","r");
	
    if (!fptr)
    {
	    printf("file can't be read!\n");
	    exit(-1);
    }
	
	fileOpenStatus = 1;
	
	fscanf(fptr, "%x", &getInstr);
	*(stage->data->Instr) = getInstr;
	
	stage->data->isInitialized = true;

#ifdef DEBUG	
	printf("instr = %x data address: 0x%x, Initialized:(%s)\r\n",*(stage->data->Instr), stage->data,
						((stage->data->isInitialized) ? "true":"false"));
#endif

}

void decode(Stage* stage)
{
	if(stage->data->isInitialized == true)
	{
		printf("Decode Instruction\n\r");
		
		stage->data->instrContents->opcode = (*(stage->data->Instr) & OPCODE_MASK) >> 26;

#ifdef DEBUG		
		printf("instr = %x data address: 0x%x, Initialized:(%s)\r\n",*(stage->data->Instr), stage->data,
							((stage->data->isInitialized) ? "true":"false"));

		printf("instr = 0x%x opcode = 0x%x\r\n",*(stage->data->Instr), (*(stage->data->Instr) & OPCODE_MASK) >> 26);
#endif
		
		switch((stage->data->instrContents)->opcode)
		{
			case 0:
				printf("ADD Instr!\r\n");
				(stage->data->instrContents)->rs = &reg.r[0] + ((*(stage->data->Instr) & RS_MASK) >> 21);
				(stage->data->instrContents)->rt = &reg.r[0] + ((*(stage->data->Instr) & RT_MASK) >> 16);
				(stage->data->instrContents)->rd = &reg.r[0] + ((*(stage->data->Instr) & R_RD_MASK) >> 11);
				printf("RS = %d, RT =%d, RD = %d \r\n",*(stage->data->instrContents->rs),*(stage->data->instrContents->rt),*(stage->data->instrContents->rd));
			break;

			case 1:
			printf("ADDI Instr!\n");
				(stage->data->instrContents)->rs = &reg.r[0] + ((*(stage->data->Instr) & RS_MASK) >> 21);
				(stage->data->instrContents)->rt = &reg.r[0] + ((*(stage->data->Instr) & RT_MASK) >> 16);
				(stage->data->instrContents)->rd = &reg.r[0] + ((*(stage->data->Instr) & R_RD_MASK) >> 11);
				//printf("RS = %d, RT =%d, RD = %d \r\n",data->instrContents->rs,data->instrContents->rt,data->instrContents->rd);
			break;
			case 2:
			printf("SUB Instr!\n");
			break;
			case 3:
			printf("SUBI Instr!\n");
			break;
			case 4:
			printf("MUL Instr!\n");
			break;
			case 5:
			printf("MULI Instr!\n");
			break;
			case 6:
			printf("OR Instr!\n");
			break;
			case 7:
			printf("ORI Instr!\n");
			break;
			case 8:
			printf("AND Instr!\n");
			break;
			case 9:
			printf("ANDI Instr!\n");
			break;
			case 10:
			printf("XOR Instr!\n");
			break;
			case 11:
			printf("XORI Instr!\n");
			break;
			case 12:
			printf("LDW Instr!\n");
			break;
			case 13:
			printf("STW Instr!\n");
			break;
			case 14:
			printf("BZ Instr!\n");
			break;
			case 15: 
			printf("BEQ Instr!\n");
			break;
			case 16: 
			printf("JR Instr!\n");
			break;
			case 17:
			printf("HALT Instr!\n");
			break;
		}
	}
}


void execute(Stage *stage)
{
	printf("Execute Instruction\n\r");

#ifdef DEBUG
	printf("instr = %x data address: 0x%x, Initialized:(%s)\r\n",*(stage->data->Instr), stage->data,
						((stage->data->isInitialized) ? "true":"false"));
#endif
						
	switch((stage->data->instrContents)->opcode)
	{
		case 0:
			printf("ADD Instr!\r\n");
			//*((stage->data->instrContents)->rd) = *((stage->data->instrContents)->rs) + *((stage->data->instrContents)->rt);
			printf("R=0x%x\n\r",*(stage->data->instrContents->rs));// + *((stage->data->instrContents)->rt));
			/*
			for(int i=0;i<32;i++)
			{	
				printf("R%d=%d",i,*((stage->data->instrContents)->rd));				

			}
			*/
		break;
	}
}		
	
void moveDataToNextStage()
{
	
	
	currIndex++;
	
#ifdef DEBUG
	uint8_t i;	
	for (i = 0; i < NUM_STAGES; i++)
	{
		printf("data[%d] address: 0x%x, data[%d]->stageID: 0x%x, Initialized:(%s)\n\r", i, &data[i], i, data[i].stageID, 
								(data[i].isInitialized) ? "true":"false"); 		
	}
#endif
}
#ifdef DEBUG

void allotFuncToStage(Stage **head, Stage **tail)
{
	Stage *temp = *head;
	int32_t i = 0;
	while(temp != *tail)
	{
		temp->id = IF + i;
		temp->func = testFunction;
		temp = temp->next;
		i++;
	}
	
}

void testFunction()
{
	printf("Started executing the function\n\r");
	
	    //uint32_t trace = 0x45C3CA56;
    uint32_t mask  = 0xFC000000;
    uint32_t trace;
    uint8_t opcode;
    char buff[2048];
 
    static FILE* fptr;

    if(!fileOpenStatus) fptr = fopen("traces.txt","r");
	
    if(!fptr)
    {
	    printf("file can't be read!\n");
	    exit(-1);
    }

    fscanf(fptr,"%s", buff);
	fileOpenStatus = 1;
    printf("Value just read: %s\n", buff);
    //fclose(fptr);

    trace = (uint32_t) strtoul(buff, NULL, 16);
 
    opcode = (trace & mask) >> 26;
    
    printf("%d\n", opcode);

    switch(opcode) {
        case 0:
        printf("ADD Instr!\n");
        break;
        case 1:
        printf("ADDI Instr!\n");
        break;
        case 2:
        printf("SUB Instr!\n");
        break;
        case 3:
        printf("SUBI Instr!\n");
        break;
        case 4:
        printf("MUL Instr!\n");
        break;
        case 5:
        printf("MULI Instr!\n");
        break;
        case 6:
        printf("OR Instr!\n");
        break;
        case 7:
        printf("ORI Instr!\n");
        break;
        case 8:
        printf("AND Instr!\n");
        break;
        case 9:
        printf("ANDI Instr!\n");
        break;
        case 10:
        printf("XOR Instr!\n");
        break;
        case 11:
        printf("XORI Instr!\n");
        break;
        case 12:
        printf("LDW Instr!\n");
        break;
        case 13:
        printf("STW Instr!\n");
        break;
        case 14:
        printf("BZ Instr!\n");
        break;
        case 15: 
        printf("BEQ Instr!\n");
        break;
        case 16: 
        printf("JR Instr!\n");
        break;
        case 17:
        printf("HALT Instr!\n");
        break;
    }
	
}


extern int r[31];


#endif



