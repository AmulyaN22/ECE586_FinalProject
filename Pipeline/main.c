#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "pipeline.h"


int32_t main(int32_t argc, char **argv)
{
	Stage *pipelineStart = NULL, *pipelineEnd = NULL;
	
	//printf("Address: 0x%x, 0x%x\n\r", (unsigned int32_t)*pipelineStart, (unsigned int32_t)*pipelineEnd);
	createPipeline(&pipelineStart, &pipelineEnd);
	
	int32_t i  =0;
	
	//printf("Address: 0x%x, 0x%x\n\r", (unsigned int32_t)*pipelineStart, (unsigned int32_t)*pipelineEnd);
	
	while(1)
	{
		Stage *temp = pipelineStart;
		
		while(temp != NULL)
		{
			printf("i:%d\n\r", i++);
			processStage(temp);
			temp = temp->next;
			//printf("temp:0x%x\n\r", (unsigned int)&temp);
			
		}
		
		moveDataToNextStage();
		printf("#######################\n\r");
		temp = pipelineStart;
	}

	return 0;
}
