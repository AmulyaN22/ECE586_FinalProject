#include <stdio.h>
#include <stdlib.h>
#include "trace_functions.h"


int main() 
{
    uint32_t mask  = 0xFC000000;
    uint32_t trace;
    uint8_t opcode;

    trace = (uint32_t) strtoul(buff, NULL, 16);
        
    opcode = (trace & mask) >> 26;
    
    printf("%d\n", opcode);

    switch(opcode) {
        case 0:
        printf("ADD instruction!\n");
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


