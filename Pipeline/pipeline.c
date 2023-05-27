#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "pipeline.h"

int32_t fileOpenStatus = 0;

Data *data;
void createPipeline(Stage **head, Stage **tail)
{
	int32_t i;

	data = (Data*) malloc(sizeof(Data));
	
	for(i = 0; i < NUM_STAGES; i++)
	{
		Stage *stagePtr = (Stage*) malloc(sizeof(Stage));
		printf("Address: 0x%x\n\r", stagePtr);
		
		stagePtr->id = IF + i;
		stagePtr->next = NULL;
		
		if(*head == NULL)
		{
			*head = stagePtr;
			*tail = stagePtr;
			
			
		}
		else{
			(*tail)->next = stagePtr;
			*tail = (*tail)->next;
		}

	}
}

void processStage(Stage *stage)
{
//#ifdef DEBUG

	switch(stage->id)
	{
		case IF: 
				printf("Instruction Fetch\n\r"); 
				stage->data = data;
				stage->func = fetch;
				break;
		case ID: 
				printf("Instruction Decode\n\r"); 
				stage->data = data;
				stage->func = decode;
				break;
		case EXE: 
				printf("Execute\n\r"); 
				stage->data = data;
				break;
		case MEM: 
				printf("MEM\n\r"); 
				stage->data = data;
				break;
		case WB: 
				printf("Write Back\n\r"); 
				stage->data = data;
				break;
		
	};
	
	stage->func(stage);
	stage->data = NULL;
	
//#endif

	
}


void fetch()
{
	uint32_t getInstr;
	fscanf(data->fptr, "%x", &getInstr);
	*(data->Instr) = getInstr;
	printf("instr = %x \r\n",*(data->Instr));
}

void decode()
{
	char opcode = 0;

	data->instrContents->opcode = (*(data->Instr) & OPCODE_MASK) >> 26;

	printf("instr = %x opcode = %d\r\n",data->Instr, (*(data->Instr) & OPCODE_MASK) >> 26);
	switch((data->instrContents)->opcode)
	{
		case 0:
			printf("ADD Instr!\r\n");
			(data->instrContents)->rs = (*(data->Instr) & RS_MASK) >> 21;
			(data->instrContents)->rt = (*(data->Instr) & RT_MASK) >> 16;
			(data->instrContents)->rd = (*(data->Instr) & R_RD_MASK) >> 11;
			printf("RS = %d, RT =%d, RD = %d \r\n",data->instrContents->rs,data->instrContents->rt,data->instrContents->rd);
		break;

		case 1:
		printf("ADDI Instr!\n");
			(data->instrContents)->rs = (*(data->Instr) & RS_MASK) >> 21;
			(data->instrContents)->rt = (*(data->Instr) & RT_MASK) >> 16;
			(data->instrContents)->rd = (*(data->Instr) & R_RD_MASK) >> 11;
			printf("RS = %d, RT =%d, RD = %d \r\n",data->instrContents->rs,data->instrContents->rt,data->instrContents->rd);
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


void execute()
{
	
	switch((data->instrContents)->opcode)
	{
		case 0:
			printf("ADD Instr!\r\n");
			(data->instrContents)->rd = (data->instrContents)->rs + (data->instrContents)->rt;
			for(int i=0;i<32;i++)
			{
				printf("R%d=%d",i,(data->instrContents)->rd);				

			}
		break;
	}
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



