import cfg
import stages
import time

mode = 0
total_instr = 0
total_stalls = 0
single_stall = 0
double_stalls = 0
total_pen = 0
total_hazards = 0
clk_cyc = 0
stalls = []

def without_forwarding():
    global total_stalls, total_hazards, stalls, single_stall, double_stalls, total_instr

    if total_instr < 1: 
        return

    curr_ins = cfg.memory_img[int(cfg.pc/4)]
    prev_ins = cfg.memory_img[int(cfg.pc/4) - 1]
    if cfg.branch_flag == 1:
         prev_prev_ins = cfg.temp_pc
    else:
        prev_prev_ins = cfg.memory_img[int(cfg.pc/4) - 2]

    if detect_hazard(curr_ins, prev_ins):
        total_stalls += 2
        double_stalls += 1
        total_hazards += 1
        stalls.append(curr_ins)
        return


    if detect_hazard(curr_ins, prev_prev_ins):
        total_stalls += 1
        single_stall += 1
        total_hazards += 1
        stalls.append(curr_ins)
        return

    cfg.branch_flag = 0


def detect_hazard(curr_ins, prev_ins):
    is_r_type = ((prev_ins >> 26) & 63) in cfg.R_based
    is_i_type = ((prev_ins >> 26) & 63) in cfg.I_based
    is_i_type_ldw = ((prev_ins >> 26) & 63) == cfg.LDW
    is_ins_Set_2 = ((curr_ins >> 26) & 63) in cfg.Ins_Set_2
    is_ins_Set_1 = ((curr_ins >> 26) & 63) in cfg.Ins_Set_1
    is_jb_based = ((prev_ins >> 26) & 63) in cfg.JB_based
    if is_ins_Set_2:
        if is_r_type and (((curr_ins >> 21) & 31) == ((prev_ins >> 11) & 31) or ((curr_ins >> 16) & 31) == ((prev_ins >> 11) & 31)):
            return True

        if is_i_type_ldw and (((curr_ins >> 21) & 31) == ((prev_ins >> 11) & 31) or ((curr_ins >> 16) & 31) == ((prev_ins >> 11) & 31)):
            return True
        if is_jb_based and (((prev_ins >> 26) & 63) == cfg.BEQ) and (((curr_ins >> 21) & 31) == ((prev_ins >> 11) & 31) or ((curr_ins >> 16) & 31) == ((prev_ins >> 11) & 31)):
            return True
        
    if is_ins_Set_1:
        if is_i_type and ((curr_ins >> 21) & 31) == ((prev_ins >> 16) & 31):
            return True

        if is_i_type_ldw and ((curr_ins >> 21) & 31) == ((prev_ins >> 16) & 31):
            return True
        
        if is_jb_based and (((prev_ins >> 26) & 63) in (cfg.BZ, cfg.JR)) and (((curr_ins >> 21) & 31) == ((prev_ins >> 16) & 31)):
            return True

    
    return False


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

    if detect_hazard_forwarding(curr_ins, prev_ins):
        total_stalls += 1
        double_stalls += 0
        total_hazards += 1
        stalls.append(curr_ins)
        return

    cfg.branch_flag = 0


def detect_hazard_forwarding(curr_ins, prev_ins):
    is_r_type = ((prev_ins >> 26) & 63) in cfg.R_based
    is_i_type = ((prev_ins >> 26) & 63) in cfg.I_based
    is_i_type_ldw = ((prev_ins >> 26) & 63) == cfg.LDW
    is_ins_Set_2 = ((curr_ins >> 26) & 63) in cfg.Ins_Set_2
    is_ins_Set_1 = ((curr_ins >> 26) & 63) in cfg.Ins_Set_1
    is_jb_based = ((prev_ins >> 26) & 63) in cfg.JB_based
    if is_ins_Set_2:
        if is_i_type_ldw and (((curr_ins >> 21) & 31) == ((prev_ins >> 11) & 31) or ((curr_ins >> 16) & 31) == ((prev_ins >> 11) & 31)):
            return True


    if is_ins_Set_1:
        if is_i_type_ldw and ((curr_ins >> 21) & 31) == ((prev_ins >> 16) & 31):
            return True
     

    
    return False

def mem_img_reader(file_path):
	with open(file_path, 'r') as file:
		for line in file:
			hex_line = int(line.strip(),16)
			cfg.memory_img.append(hex_line) 


mode = input("Get MIPS-Lite Simulator Mode = ")
mode = int(mode)	

print("\n")
mem_img_reader("/u/nik23/Desktop/ECE586_FinalProject/final_proj_trace.txt")

while cfg.opcode != 17 :

    stages.fetch() 
    stages.decode(cfg.instr)

    if(mode == 1):
        without_forwarding()

    if(mode == 2):
           with_forwarding()
            
    stages.execute(cfg.opcode,cfg.Rs,cfg.Rt,cfg.Rd,cfg.imm,cfg.r)
    stages.memory()
    stages.write_back()

    total_instr += 1
    clk_cyc += 1


if(mode == 0):
    print("////////// Functional Simulator /////////")

if(mode == 1):
    print("////////// Functional Simulator without forwarding /////////")

if(mode == 2):
    print("////////// Functional Simulator with forwarding /////////")

print("Total Instr = " + str(total_instr))
print("Arithmetic Instructions = ",cfg.arith_instr)
print("Logical Instructions = ",cfg.logical_instr)
print("Memory Access Instructions = ",cfg.mem_instr)
print("Control Transfer Instructions = ",cfg.cntrl_instr)

if((mode == 1) or (mode==2)):
    print("\n")
    print("Total Clocks = " + str(clk_cyc +total_stalls+cfg.total_pen+4))
    print("Total Hazards = " + str(total_hazards))
    print("Total Penalty = " + str(cfg.total_pen))
    print("Total Stalls = " + str(total_stalls))

print("\n")
print("****Register Contents****")
for i in range(0,31):
    print("R"+str(i) + " = " + str(cfg.r[i]))
print("\n")
print("****Memory Contents*****")
for x in cfg.data_mem:
    print(x,':',cfg.data_mem[x])

