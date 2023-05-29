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

typedef enum pipelineStages{IF = 0, ID = 1, EXE = 2, MEM = 3, WB = 4} pipelineStages;

typedef struct
{
    uint8_t opcode;
    uint32_t *rs;
    uint32_t *rt;
    uint32_t *rd;
    uint8_t imm;
}instr_contents;

typedef struct
{
	uint32_t r[32];
	uint32_t pc;
} Reg_File;

typedef struct Data
{
	bool isInitialized;
	pipelineStages stageID;
	uint32_t *Instr;
	instr_contents *instrContents;
} Data;


typedef struct Stage
{
	pipelineStages id;
	void (*func)(struct Stage *temp);
	bool isDataAssigned;
	struct Data *data;
	struct Stage *next;
} Stage;

extern Data *data;
extern uint32_t currIndex;
void createPipeline(Stage **head, Stage **tail);
void processStage(Stage *stage);
void fetch(Stage *stage);
void decode(Stage *stage);
void execute(Stage *stage);
void moveDataToNextStage();

#ifdef DEBUG
void allotFuncToStage(Stage **head, Stage **tail);
void testFunction();


#endif

#endif