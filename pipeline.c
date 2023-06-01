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
			output->rs = (instruction & RS_MASK) >> 21;
			output->rt = (instruction & RT_MASK) >> 16;
			output->imm = (instruction & I_IMM_MASK);	
			printf("RS = %d, RT =%d, IMM = %d \r\n",output->rs,output->rt,output->imm);
		break;
		case 2:
			printf("SUB instruction!\n");
			output->rs = (instruction & RS_MASK) >> 21;
			output->rt = (instruction & RT_MASK) >> 16;
			output->rd = (instruction & R_RD_MASK) >> 11;
			printf("RS = %d, RT =%d, RD = %d \r\n",output->rs,output->rt,output->rd);
		break;
		case 3:
			printf("SUBI instruction!\n");
			output->rs = (instruction & RS_MASK) >> 21;
			output->rt = (instruction & RT_MASK) >> 16;
			output->imm = (instruction & I_IMM_MASK);
			printf("RS = %d, RT =%d, IMM = %d \r\n",output->rs,output->rt,output->imm);
		break;
		case 4:
			printf("MUL instruction!\n");
			output->rs = (instruction & RS_MASK) >> 21;
			output->rt = (instruction & RT_MASK) >> 16;
			output->rd = (instruction & R_RD_MASK) >> 11;
			printf("RS = %d, RT =%d, RD = %d \r\n",output->rs,output->rt,output->rd);
		break;
		case 5:
			printf("MULI instruction!\n");
			output->rs = (instruction & RS_MASK) >> 21;
			output->rt = (instruction & RT_MASK) >> 16;
			output->imm = (instruction & I_IMM_MASK);
			printf("RS = %d, RT =%d, IMM = %d \r\n",output->rs,output->rt,output->imm);
		break;			
		case 6:
			printf("OR instruction!\n");
			output->rs = (instruction & RS_MASK) >> 21;
			output->rt = (instruction & RT_MASK) >> 16;
			output->rd = (instruction & R_RD_MASK) >> 11;
			printf("RS = %d, RT =%d, RD = %d \r\n",output->rs,output->rt,output->rd);
		break;			
				
		case 7:
			printf("ORI instruction!\n");
			output->rs = (instruction & RS_MASK) >> 21;
			output->rt = (instruction & RT_MASK) >> 16;
			output->imm = (instruction & I_IMM_MASK);
			printf("RS = %d, RT =%d, IMM = %d \r\n",output->rs,output->rt,output->imm);
		break;			
		case 8:
			printf("AND instruction!\n");
			output->rs = (instruction & RS_MASK) >> 21;
			output->rt = (instruction & RT_MASK) >> 16;
			output->rd = (instruction & R_RD_MASK) >> 11;
			printf("RS = %d, RT =%d, RD = %d \r\n",output->rs,output->rt,output->rd);
		break;				
		case 9:
			printf("ANDI instruction!\n");
			output->rs = (instruction & RS_MASK) >> 21;
			output->rt = (instruction & RT_MASK) >> 16;
			output->imm = (instruction & I_IMM_MASK);
			printf("RS = %d, RT =%d, IMM = %d \r\n",output->rs,output->rt,output->imm);
		break;			
		case 10:
			printf("XOR instruction!\n");
			output->rs = (instruction & RS_MASK) >> 21;
			output->rt = (instruction & RT_MASK) >> 16;
			output->rd = (instruction & R_RD_MASK) >> 11;
			printf("RS = %d, RT =%d, RD = %d \r\n",output->rs,output->rt,output->rd);
		break;						
		case 11:
			printf("XORI instruction!\n");
			output->rs = (instruction & RS_MASK) >> 21;
			output->rt = (instruction & RT_MASK) >> 16;
			output->imm = (instruction & I_IMM_MASK);
			printf("RS = %d, RT =%d, IMM = %d \r\n",output->rs,output->rt,output->imm);
		break;			
		case 12:
			printf("LDW instruction!\n");
			output->rs = (instruction & RS_MASK) >> 21;
			output->rt = (instruction & RT_MASK) >> 16;
			output->imm = (instruction & I_IMM_MASK);
			printf("RS = %d, RT =%d, IMM = %d \r\n",output->rs,output->rt,output->imm);
		break;
		case 13:
			printf("STW instruction!\n");
			output->rs = (instruction & RS_MASK) >> 21;
			output->rt = (instruction & RT_MASK) >> 16;
			output->imm = (instruction & I_IMM_MASK);
			printf("RS = %d, RT =%d, IMM = %d \r\n",output->rs,output->rt,output->imm);
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
		case 1:
			printf("ADDI instruction!\r\n");
			r[input->rt] = r[input->rs] + input->imm;
			for(int i=0;i<32;i++)
			{
				printf("R%d=%d",i,r[i]);				
				
			}
		break;
		case 2:
			printf("SUB instruction!\r\n");
			r[input->rd] = r[input->rs] - r[input->rt];
			for(int i=0;i<32;i++)
			{
				printf("R%d=%d",i,r[i]);				
				
			}
		break;
		case 3:
			printf("SUBI instruction!\r\n");
			r[input->rt] = r[input->rs] + input->imm;
			for(int i=0;i<32;i++)
			{
				printf("R%d=%d",i,r[i]);				
				
			}
		break;
		case 4:
			printf("MUL instruction!\r\n");
			r[input->rd] = r[input->rs] * r[input->rt];
			for(int i=0;i<32;i++)
			{
				printf("R%d=%d",i,r[i]);				
				
			}
		break;
		case 5:
			printf("MULI instruction!\r\n");
			r[input->rt] =r[input->rs] * input->imm;
			for(int i=0;i<32;i++)
			{
				printf("R%d=%d",i,r[i]);				
				
			} 
		break;
		case 6:
			printf("OR instruction!\r\n");
			r[input->rd] = r[input->rs] | r[input->rt];
			for(int i=0;i<32;i++)
			{
				printf("R%d=%d",i,r[i]);				
				
			}
		break;
		case 7:
			printf("ORI instruction!\r\n");
			r[input->rt] = r[input->rs] | input->imm;
			for(int i=0;i<32;i++)
			{
				printf("R%d=%d",i,r[i]);				
				
			}
		break;
		case 8:
			printf("AND instruction!\r\n");
			r[input->rd] = r[input->rs] & r[input->rt];
			for(int i=0;i<32;i++)
			{
				printf("R%d=%d",i,r[i]);				
				
			}
		break;
		case 9:
			printf("ANDI instruction!\r\n");
			r[input->rt] = r[input->rs] & input->imm;
			for(int i=0;i<32;i++)
			{
				printf("R%d=%d",i,r[i]);				
				
			}
		break;
		case 10:
			printf("XOR instruction!\r\n");
			r[input->rd] = r[input->rs] ^ r[input->rt];
			for(int i=0;i<32;i++)
			{
				printf("R%d=%d",i,r[i]);				
				
			}
		break;
		case 11:
			printf("XORI instruction!\r\n");
			r[input->rt] = r[input->rs] ^ input->imm;
			for(int i=0;i<32;i++)
			{
				printf("R%d=%d",i,r[i]);				
				
			}
		break;
			
	}
}		 
