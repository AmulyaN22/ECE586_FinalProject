#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "pipeline.h"

int32_t fileOpenStatus = 0;

void createPipeline(Stage **head, Stage **tail)
{
	int32_t i;

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
#ifdef DEBUG

	switch(stage->id)
	{
		case IF: printf("Instruction Fetch\n\r"); break;
		case ID: printf("Instruction Decode\n\r"); break;
		case EXE: printf("Execute\n\r"); break;
		case MEM: printf("MEM\n\r"); break;
		case WB: printf("Write Back\n\r"); break;
		
	};
	stage->func(stage);
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
        printf("ADD instruction!\n");
        break;
        case 1:
        printf("ADDI instruction!\n");
        break;
        case 2:
        printf("SUB instruction!\n");
        break;
        case 3:
        printf("SUBI instruction!\n");
        break;
        case 4:
        printf("MUL instruction!\n");
        break;
        case 5:
        printf("MULI instruction!\n");
        break;
        case 6:
        printf("OR instruction!\n");
        break;
        case 7:
        printf("ORI instruction!\n");
        break;
        case 8:
        printf("AND instruction!\n");
        break;
        case 9:
        printf("ANDI instruction!\n");
        break;
        case 10:
        printf("XOR instruction!\n");
        break;
        case 11:
        printf("XORI instruction!\n");
        break;
        case 12:
        printf("LDW instruction!\n");
        break;
        case 13:
        printf("STW instruction!\n");
        break;
        case 14:
        printf("BZ instruction!\n");
        break;
        case 15: 
        printf("BEQ instruction!\n");
        break;
        case 16: 
        printf("JR instruction!\n");
        break;
        case 17:
        printf("HALT instruction!\n");
        break;
    }
	
}
#endif



