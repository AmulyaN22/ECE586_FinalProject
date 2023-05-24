#include "MIPS.h"
#include <string.h>

char buffer[1024];

void main()
{
    FILE* memimage;
    int instr;
    memimage = fopen("traces.txt","r");

    if(memimage)
    {
	while (fscanf(memimage, "%d", &instr) == 1) {
	
            printf("%d\n", instr);		
	    //printf("%x\r\n",hexValue);
	    execute(instr);
        }

    }
    else
        printf("file can't be read!\n");
    
}
