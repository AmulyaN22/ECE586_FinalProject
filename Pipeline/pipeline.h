#ifndef __PIPELINE_H__
#define __PIPELINE_H__

#include <stdint.h>

typedef enum pipelineStages{IF, ID, EXE, MEM, WB} pipelineStages;

typedef struct Data{
	int32_t x;
	int32_t y;
} Data;


typedef struct Stage
{
	pipelineStages id;
	void (*func)(struct Stage *temp);
	struct Data *data;
	struct Stage *next;
} Stage;

#define NUM_STAGES 5

void createPipeline(Stage **head, Stage **tail);
void processStage(Stage *stage);

#ifdef DEBUG
void allotFuncToStage(Stage **head, Stage **tail);
void testFunction();

#endif

#endif