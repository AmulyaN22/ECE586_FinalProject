import cfg
import stages



def mem_img_reader(file_path):
	with open('/u/nik23/Desktop/ECE586_FinalProject/traces.txt', 'r') as file:
		for line in file:
			hex_line = int(line.strip(),16)
			cfg.memory_img.append(hex_line)  

	
mem_img_reader("traces.txt")

while cfg.opcode != 17 :
    stages.fetch() 
    stages.decode(cfg.memory_img[cfg.instr])
    stages.execute(cfg.opcode,cfg.Rs,cfg.Rt,cfg.Rd,cfg.imm,cfg.r)
    print(cfg.opcode,cfg.Rs,cfg.Rt,cfg.Rd,cfg.imm,cfg.r)

#unsigned_int = 32769

#signed_int = ctypes.c_int16(unsigned_int).value
#print(signed_int)

