#ifndef __PIPELINE_H__
#define __PIPELINE_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define   OPCODE_MASK (0xFC000000)
#define   RS_MASK     (0x03E00000)
#define   RT_MASK     (0x001F0000)  
#define   R_RD_MASK   (0x0000F800)
#define   I_IMM_MASK  (0x0000FFFF)
#define NUM_STAGES 5

typedef enum pipelineStages{IF, ID, EXE, MEM, WB} pipelineStages;

typedef struct{

    uint8_t opcode;
    uint8_t rs;
    uint8_t rt;
    uint8_t rd;
    uint8_t imm;
}instr_contents;

typedef struct Data{
	int32_t x;
	int32_t y;
	uint32_t *Instr;
	instr_contents *instrContents;
	
	FILE* fptr;
	
} Data;


typedef struct Stage
{
	pipelineStages id;
	void (*func)(struct Stage *temp);
	bool isDataAssigned;
	struct Data *data;
	struct Stage *next;
} Stage;

extern int i[31];
extern Data *data;
void createPipeline(Stage **head, Stage **tail);
void processStage(Stage *stage);
void fetch();
void decode();
//void execute(instr_contents *input);

#ifdef DEBUG
void allotFuncToStage(Stage **head, Stage **tail);
void testFunction();


#endif

#endif