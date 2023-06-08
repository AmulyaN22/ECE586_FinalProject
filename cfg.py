opcode = 0
Rs = 0
Rt = 0
Rd = 0
imm = 0
instr = 0
mem_flag = 0
data_mem = {}
memory_img = []
r = [0]*32
pc = 0

temp_pc = 0
branch_flag = 0
total_pen = 0
stall_pen = 0
branch_taken = 0

ADD  = 0
ADDI = 1
SUB  = 2
SUBI = 3
MUL  = 4
MULI = 5
OR   = 6
ORI  = 7
AND  = 8
ANDI = 9
XOR  = 10
XORI = 11
LDW  = 12
STW  = 13
BZ   = 14
BEQ  = 15
JR   = 16
HALT = 17

R_based = [ADD,SUB,MUL,OR,AND,XOR]
I_based = [ADDI,SUBI,MULI,ORI,ANDI,XORI]
JB_based = [LDW,STW,BZ,BEQ,JR,HALT]
Ins_Set_2 = [ADD,SUB,MUL,OR,AND,XOR,BEQ]
Ins_Set_1 = [ADDI,SUBI,MULI,ORI,ANDI,XORI,LDW,BZ,JR]


exe_reg = [0,0]
mem_reg = 0
wb_reg = 0