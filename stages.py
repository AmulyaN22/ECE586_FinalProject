import cfg
import ctypes


def fetch():
	cfg.instr = int(cfg.pc/4)
	if(cfg.opcode != 17):
		cfg.pc+=4


def decode(instr):
	cfg.opcode = (instr & 0xFC000000)>> 26   
	cfg.Rs     = (instr & 0x03E00000)>> 21
	cfg.Rt     = (instr & 0x001F0000)>> 16
	cfg.Rd     = (instr & 0x0000F800)>> 11
	cfg.imm    = (instr & 0x0000FFFF)>> 11

def execute(opcode,Rs,Rt,Rd,imm,r):
	r[6] = 32769
	r[3] = 2
	match opcode:
		case 0:
			r[Rd] = ctypes.c_int16(r[Rs]).value + ctypes.c_int16(r[Rt]).value	
		case 1:
			r[Rt] = ctypes.c_int16(r[Rs]).value + ctypes.c_int16(imm).value	
		case 2:
			r[Rd] = ctypes.c_int16(r[Rs]).value - ctypes.c_int16(r[Rt]).value	
		case 3:
			r[Rt] = ctypes.c_int16(r[Rs]).value - ctypes.c_int16(imm).value	
		case 4:
			r[Rd] = ctypes.c_int16(r[Rs]).value * ctypes.c_int16(r[Rt]).value	
		case 5:
			r[Rt] = ctypes.c_int16(r[Rs]).value * ctypes.c_int16(imm).value	
		case 6:
			r[Rd] = ctypes.c_int16(r[Rs]).value | ctypes.c_int16(r[Rt]).value	
		case 7:
			r[Rt] = ctypes.c_int16(r[Rs]).value | ctypes.c_int16(imm).value		
		case 8:
			r[Rd] = ctypes.c_int16(r[Rs]).value & ctypes.c_int16(r[Rt]).value	
		case 9:
			r[Rt] = ctypes.c_int16(r[Rs]).value & ctypes.c_int16(imm).value	
		case 10:
			r[Rd] = ctypes.c_int16(r[Rs]).value ^ ctypes.c_int16(r[Rt]).value	
		case 11:
			r[Rt] = ctypes.c_int16(r[Rs]).value ^ ctypes.c_int16(imm).value	
