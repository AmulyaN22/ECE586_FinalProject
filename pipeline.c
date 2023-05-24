#include "MIPS.h"

char *fetch(char buff[1024],FILE* fptr)
{
	return fgets(buff, sizeof buff,fptr);
    
}

void execute(int instruction)
{
	char opcode = 0;

	opcode = (instruction & 0xFC000000) >> 26;

	switch(opcode)
	{
		case 0:
		printf("ADD instruction!\r\n");
		break;
		/*
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
		*/
	}
}
