#include <stdio.h>
#include <stdint.h>
#include "pipeline.h"


int32_t main(int32_t argc, char **argv)
{
	Stage *pipelineStart = NULL, *pipelineEnd = NULL;
	
	//printf("Address: 0x%x, 0x%x\n\r", (unsigned int32_t)*pipelineStart, (unsigned int32_t)*pipelineEnd);
	createPipeline(&pipelineStart, &pipelineEnd);
	
	//printf("Address: 0x%x, 0x%x\n\r", (unsigned int32_t)*pipelineStart, (unsigned int32_t)*pipelineEnd);
	
#ifdef DEBUG
	printf("Starting the MIPS LITE SIMULATOR\n\r");
	allotFuncToStage(&pipelineStart, &pipelineEnd);
	Stage *temp = pipelineStart;
	
	int32_t i  =0;
	while(temp != pipelineEnd)
	{
		printf("i:%d\n\r", i);
		processStage(temp);
		temp = temp->next;
	}
#else
	while(1)
	{
		Stage *temp = pipelineStart;
		
		while(temp != pipelineEnd)
		{
			printf("i:%d\n\r", i);
			processStage(temp);
			temp = temp->next;
		}
		
		*temp = pipelineStart;
	}
#endif

	return 0;
}
