#include "MIPS.h"
#include <string.h>

char buffer[1024];
int r[32];

void main()
{
    r[2] = 3;
    r[3] = 1;
    FILE* memimage;
    unsigned int instr;
    instr_contents pipe1_op;

    memimage = fopen("traces.txt","r");

    if(memimage)
    {
	while (fetch(&instr,memimage) == 1) 
    {
	
        printf("%x\n", instr);		
	    //printf("%x\r\n",hexValue);
	    decode(instr,&pipe1_op);
        execute(&pipe1_op);
    }

    }
    else
        printf("file can't be read!\n");
    
}
