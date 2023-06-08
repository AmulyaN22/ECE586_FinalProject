import cfg
import stages
import time

total_instr = 0
total_stalls = 0
single_stall = 0
double_stalls = 0
total_pen = 0
total_hazards = 0
clk_cyc = 0
stalls = []



def with_forwarding():
    global total_stalls, total_hazards, stalls, single_stall, double_stalls, total_instr

    if total_instr < 1: 
        return

    curr_ins = cfg.memory_img[int(cfg.pc/4)]
    prev_ins = cfg.memory_img[int(cfg.pc/4) - 1]
    if cfg.branch_flag == 1:
         prev_prev_ins = cfg.temp_pc
    else:
        prev_prev_ins = cfg.memory_img[int(cfg.pc/4) - 2]

    if is_hazardous(curr_ins, prev_ins):
        print("yes!")
        total_stalls += 1
        double_stalls += 0
        total_hazards += 1
        stalls.append(curr_ins)
        return

    '''
    if is_hazardous(curr_ins, prev_prev_ins):
        total_stalls += 1
        single_stall += 1
        total_hazards += 1
        stalls.append(curr_ins)
        return
    '''

    cfg.branch_flag = 0


def is_hazardous(curr_ins, prev_ins):
    is_r_type = ((prev_ins >> 26) & 63) in cfg.R_based
    is_i_type = ((prev_ins >> 26) & 63) in cfg.I_based
    is_i_type_ldw = ((prev_ins >> 26) & 63) == cfg.LDW
    is_ins_Set_2 = ((curr_ins >> 26) & 63) in cfg.Ins_Set_2
    is_ins_Set_1 = ((curr_ins >> 26) & 63) in cfg.Ins_Set_1
    is_jb_based = ((prev_ins >> 26) & 63) in cfg.JB_based
    if is_ins_Set_2:
        '''
        if is_r_type and (((curr_ins >> 21) & 31) == ((prev_ins >> 11) & 31) or ((curr_ins >> 16) & 31) == ((prev_ins >> 11) & 31)):
            return True
        '''

        if is_i_type_ldw and (((curr_ins >> 21) & 31) == ((prev_ins >> 11) & 31) or ((curr_ins >> 16) & 31) == ((prev_ins >> 11) & 31)):
            return True
        '''
        if is_jb_based and (((prev_ins >> 26) & 63) == cfg.BEQ) and (((curr_ins >> 21) & 31) == ((prev_ins >> 11) & 31) or ((curr_ins >> 16) & 31) == ((prev_ins >> 11) & 31)):
            return True
        '''

    if is_ins_Set_1:
        '''
        if is_i_type and ((curr_ins >> 21) & 31) == ((prev_ins >> 16) & 31):
            return True
        '''

        if is_i_type_ldw and ((curr_ins >> 21) & 31) == ((prev_ins >> 16) & 31):
            return True
        '''
        if is_jb_based and (((prev_ins >> 26) & 63) in (cfg.BZ, cfg.JR)) and (((curr_ins >> 21) & 31) == ((prev_ins >> 16) & 31)):
            return True
        '''

    
    return False

def mem_img_reader(file_path):
	with open(file_path, 'r') as file:
		for line in file:
			hex_line = int(line.strip(),16)
			cfg.memory_img.append(hex_line) 


	
mem_img_reader("C:/Users/jadha/OneDrive/Desktop/ECE-586/compArch_Proj/ECE586_FinalProject-Python/final_proj_trace.txt")

while cfg.opcode != 17 :

    stages.fetch() 

    stages.decode(cfg.instr)
    with_forwarding()
    stages.execute(cfg.opcode,cfg.Rs,cfg.Rt,cfg.Rd,cfg.imm,cfg.r)

    stages.memory()
    #print(hex(cfg.instr),'pc'+str(cfg.pc),cfg.opcode,cfg.Rs,cfg.Rt,cfg.Rd,cfg.imm,cfg.r,cfg.data_mem)
    #time.sleep(0.5)
    total_instr += 1
    clk_cyc += 1
    print(clk_cyc)
    #print(cfg.pc,cfg.r,cfg.data_mem)
    #print()
#print((cfg.memory_img[cfg.pc] & 0xFC000000)>> 26)

#unsigned_int = 32769

#signed_int = ctypes.c_int16(unsigned_int).value
print(total_hazards)
print(total_pen)
print(clk_cyc +total_stalls+cfg.total_pen+4)
print(single_stall, double_stalls)
print(cfg.branch_taken)
