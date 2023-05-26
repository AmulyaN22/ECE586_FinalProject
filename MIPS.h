#ifndef MIPS
#define MIPS

#include <stdio.h>
#include <stdlib.h>

#define   OPCODE_MASK (0xFC000000)
#define   RS_MASK     (0x03E00000)
#define   RT_MASK     (0x001F0000)  
#define   R_RD_MASK   (0x0000F800)

#define   I_IMM_MASK  (0x0000FFFF)

typedef struct{

    unsigned char opcode;
    unsigned char rs;
    unsigned char rt;
    unsigned char rd;
    unsigned char imm;
}instr_contents;

extern int i[31];

int fetch(unsigned int *getInstr,FILE* fptr);
void decode(int instruction, instr_contents *input);
void execute(instr_contents *input);




#endif










