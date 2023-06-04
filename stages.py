import cfg
import ctypes


def fetch():
	cfg.instr = cfg.memory_img[int(cfg.pc/4)]
	if(cfg.opcode != 17):
		cfg.pc+=4


def decode(instr):
	cfg.opcode = (instr & 0xFC000000)>> 26   
	cfg.Rs     = (instr & 0x03E00000)>> 21
	cfg.Rt     = (instr & 0x001F0000)>> 16
	cfg.Rd     = (instr & 0x0000F800)>> 11
	cfg.imm    = (instr & 0x0000FFFF)


def execute(opcode,Rs,Rt,Rd,imm,r):
	match opcode:
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
				cfg.pc-=4
				cfg.pc = (cfg.pc + (4 * ctypes.c_int16(imm).value))	
		case 15:
			if(cfg.r[cfg.Rs] == cfg.r[cfg.Rt]):
				cfg.pc-=4
				cfg.pc = (cfg.pc + (4 * ctypes.c_int16(imm).value))
		case 16:
			cfg.pc = r[Rs]						

def memory():
	if(cfg.mem_flag and cfg.opcode == 12):
		mem_addr = (cfg.r[cfg.Rs] + ctypes.c_int16(cfg.imm).value)/4
		cfg.r[cfg.Rt] = ctypes.c_int32(cfg.memory_img[mem_addr]).value
		cfg.mem_flag = 0
	if(cfg.mem_flag and cfg.opcode == 13):
		mem_addr = (cfg.r[cfg.Rs] + ctypes.c_int16(cfg.imm).value)/4
		cfg.memory_img[mem_addr] = cfg.r[cfg.Rt]
		cfg.data_mem[4 * mem_addr] = cfg.memory_img[mem_addr]
		cfg.mem_flag = 0
