#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

int main()
{

uint32_t trace;
char buff[2048];
FILE* fptr;

    fptr = fopen("traces.txt","r");

    if(!fptr)
    {
	    printf("file can't be read!\n");
	    exit(-1);
    }

    fscanf(fptr,"%s", buff);
    //printf("Value just read: %s\n", buff);
    fclose(fptr);

    trace = (uint32_t) strtoul(buff, NULL, 10);
    
    printf("%s to %u\n",buff,trace);

    return 0;

}


