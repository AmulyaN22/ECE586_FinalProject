#include "MIPS.h"

extern int r[31];

int fetch(unsigned int *getInstr,FILE* fptr)
{
	return fscanf(fptr, "%x", getInstr);
    
}

void decode(int instruction, instr_contents *output)
{
	char opcode = 0;

	output->opcode = (instruction & OPCODE_MASK) >> 26;

	printf("instr = %d opcode = %d\r\n",instruction,output->opcode);
	switch(output->opcode)
	{
		case 0:
			printf("ADD instruction!\r\n");
			output->rs = (instruction & RS_MASK) >> 21;
			output->rt = (instruction & RT_MASK) >> 16;
			output->rd = (instruction & R_RD_MASK) >> 11;
			printf("RS = %d, RT =%d, RD = %d \r\n",output->rs,output->rt,output->rd);
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


void execute(instr_contents *input)
{
	
	switch(input->opcode)
	{
		case 0:
			printf("ADD instruction!\r\n");
			r[input->rd] = r[input->rs] + r[input->rt];
			for(int i=0;i<32;i++)
			{
				printf("R%d=%d",i,r[i]);				

			}
		break;
	}
}		
