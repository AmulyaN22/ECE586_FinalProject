import cfg
import ctypes
 
def fetch():
	cfg.instr = cfg.memory_img[int(cfg.pc/4)]
	if(cfg.opcode != 17):
		cfg.pc+=4
	elif(cfg.stall_pen != 0):
		cfg.opcode = 18   
		cfg.Rs     = 0
		cfg.Rt     = 0
		cfg.Rd     = 0
		cfg.imm    = 0
		cfg.instr  = 18 << 26
		cfg.stall_pen -= 1



def decode(instr):
	cfg.opcode = (instr & 0xFC000000)>> 26   
	cfg.Rs     = (instr & 0x03E00000)>> 21
	cfg.Rt     = (instr & 0x001F0000)>> 16
	cfg.Rd     = (instr & 0x0000F800)>> 11
	cfg.imm    = (instr & 0x0000FFFF)


def execute(opcode,Rs,Rt,Rd,imm,r):
	match (opcode):
		case 0:
			r[Rd] = r[Rs] + r[Rt]	
		case 1:
			r[Rt] = r[Rs] + ctypes.c_int16(imm).value
		case 2:
			r[Rd] = r[Rs] - r[Rt]	
		case 3:
			r[Rt] = r[Rs] - ctypes.c_int16(imm).value	
		case 4:
			r[Rd] = r[Rs] * r[Rt]	
		case 5:
			r[Rt] = r[Rs] * ctypes.c_int16(imm).value	
		case 6:
			r[Rd] = r[Rs] | r[Rt]	
		case 7:
			r[Rt] = r[Rs] | imm	
		case 8:
			r[Rd] = r[Rs] & r[Rt]	
		case 9:
			r[Rt] = r[Rs] & imm
		case 10:
			r[Rd] = r[Rs] ^ r[Rt]	
		case 11:
			r[Rt] = r[Rs] ^ imm
		case 12:
			cfg.mem_flag = 1
		case 13:
			cfg.mem_flag = 1
		case 14:
			if(r[Rs] == 0):
				print('dfvrfrfrfsrfsrfsrfsfsefesfseffffffffffffffffffffffffff')
				cfg.pc-=4
				cfg.branch_flag = 1
				cfg.temp_pc = cfg.pc - 4
				cfg.pc = (cfg.pc + (4 * ctypes.c_int16(imm).value))	
				cfg.stall_pen = 2
				cfg.total_pen += 2
				cfg.branch_taken +=1
		case 15:
			if(cfg.r[cfg.Rs] == cfg.r[cfg.Rt]):
				print('dfvrfrfrfsrfsrfsrfsfsefesfseffffffffffffffffffffffffff')
				cfg.pc-=4
				cfg.branch_flag = 1
				cfg.temp_pc = cfg.pc - 4
				cfg.pc = (cfg.pc + (4 * ctypes.c_int16(imm).value))
				cfg.stall_pen = 2
				cfg.total_pen += 2
				cfg.branch_taken +=1
		case 16:
			print('dfvrfrfrfsrfsrfsrfsfsefesfseffffffffffffffffffffffffff')
			cfg.pc = r[Rs]
			cfg.branch_flag = 1
			cfg.temp_pc = cfg.pc - 4
			cfg.stall_pen = 2
			cfg.total_pen += 2
			cfg.branch_taken +=1
		
		case 18:
			cfg.Rs     = 0
			cfg.Rt     = 0
			cfg.Rd     = 0
			cfg.imm    = 0
	
	cfg.exe_reg[1] = cfg.exe_reg[0]
	if opcode in cfg.R_based :
		cfg.exe_reg[0] = Rd
	elif opcode in cfg.I_based:
		cfg.exe_reg[0] = Rt
		


def memory():
	if(cfg.mem_flag and cfg.opcode == 12):
		mem_addr = int((cfg.r[cfg.Rs] + ctypes.c_int16(cfg.imm).value)/4)
		cfg.r[cfg.Rt] = ctypes.c_int32(cfg.memory_img[mem_addr]).value
		cfg.mem_flag = 0
		cfg.mem_reg = cfg.Rt
	if(cfg.mem_flag and cfg.opcode == 13):
		mem_addr = int((cfg.r[cfg.Rs] + ctypes.c_int16(cfg.imm).value)/4)
		print("addr = " + str(mem_addr))
		cfg.memory_img[mem_addr] = cfg.r[cfg.Rt]
		cfg.data_mem[int(mem_addr * 4)] = cfg.memory_img[mem_addr]
		cfg.mem_flag = 0

def write_back(output):
    global opcode,temp_reg,Rd,Rt
    if(opcode in R_TYPE):
        temp_reg[Rd] = output
        reg_dict[Rd] = temp_reg[Rd]
    elif(opcode in I_TYPE or opcode == LDW):
        temp_reg[Rt] = output
        reg_dict[Rt] = temp_reg[Rt]
