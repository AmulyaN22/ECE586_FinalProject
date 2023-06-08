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
			cfg.arith_instr +=1
			r[Rd] = r[Rs] + r[Rt]	
		case 1:
			cfg.arith_instr +=1
			r[Rt] = r[Rs] + ctypes.c_int16(imm).value
		case 2:
			cfg.arith_instr +=1
			r[Rd] = r[Rs] - r[Rt]	
		case 3:
			cfg.arith_instr +=1
			r[Rt] = r[Rs] - ctypes.c_int16(imm).value	
		case 4:
			cfg.arith_instr +=1
			r[Rd] = r[Rs] * r[Rt]	
		case 5:
			cfg.arith_instr +=1
			r[Rt] = r[Rs] * ctypes.c_int16(imm).value	
		case 6:
			cfg.logical_instr +=1
			r[Rd] = r[Rs] | r[Rt]	
		case 7:
			cfg.logical_instr +=1
			r[Rt] = r[Rs] | imm	
		case 8:
			cfg.logical_instr +=1
			r[Rd] = r[Rs] & r[Rt]	
		case 9:
			cfg.logical_instr +=1
			r[Rt] = r[Rs] & imm
		case 10:
			cfg.logical_instr +=1
			r[Rd] = r[Rs] ^ r[Rt]	
		case 11:
			cfg.logical_instr +=1
			r[Rt] = r[Rs] ^ imm
		case 12:
			cfg.mem_instr+=1
			cfg.mem_flag = 1
		case 13:
			cfg.mem_instr+=1
			cfg.mem_flag = 1
		case 14:
			cfg.cntrl_instr+=1
			if(r[Rs] == 0):
				cfg.pc-=4
				cfg.branch_flag = 1
				cfg.temp_pc = cfg.pc - 4
				cfg.pc = (cfg.pc + (4 * ctypes.c_int16(imm).value))	
				cfg.stall_pen = 2
				cfg.total_pen += 2
				cfg.branch_taken +=1
		case 15:
			cfg.cntrl_instr+=1
			if(cfg.r[cfg.Rs] == cfg.r[cfg.Rt]):

				cfg.pc-=4
				cfg.branch_flag = 1
				cfg.temp_pc = cfg.pc - 4
				cfg.pc = (cfg.pc + (4 * ctypes.c_int16(imm).value))
				cfg.stall_pen = 2
				cfg.total_pen += 2
				cfg.branch_taken +=1
		case 16:
			cfg.cntrl_instr+=1
			cfg.pc = r[Rs]
			cfg.branch_flag = 1
			cfg.temp_pc = cfg.pc - 4
			cfg.stall_pen = 2
			cfg.total_pen += 2
			cfg.branch_taken +=1
		
		case 17:
			cfg.cntrl_instr+=1
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
	

def write_back():
	if(cfg.mem_flag and cfg.opcode == 13):
		mem_addr = int((cfg.r[cfg.Rs] + ctypes.c_int16(cfg.imm).value)/4)
		cfg.memory_img[mem_addr] = cfg.r[cfg.Rt]
		cfg.data_mem[int(mem_addr * 4)] = cfg.memory_img[mem_addr]
		cfg.mem_flag = 0
