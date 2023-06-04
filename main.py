import cfg
import stages
import time

total_instr = 0

def mem_img_reader(file_path):
	with open(file_path, 'r') as file:
		for line in file:
			hex_line = int(line.strip(),16)
			cfg.memory_img.append(hex_line)  


	
mem_img_reader("/u/nik23/Desktop/ECE586_FinalProject/ece586 sample_memory_image.txt")

while cfg.opcode != 17 :

    stages.fetch() 

    stages.decode(cfg.instr)
    stages.execute(cfg.opcode,cfg.Rs,cfg.Rt,cfg.Rd,cfg.imm,cfg.r)

    stages.memory()
    #print(hex(cfg.instr),'pc'+str(cfg.pc),cfg.opcode,cfg.Rs,cfg.Rt,cfg.Rd,cfg.imm,cfg.r)
    #time.sleep(0.5)
    total_instr += 1
    print(total_instr)
    #print(cfg.pc,cfg.r,cfg.data_mem)
    #print()
#print((cfg.memory_img[cfg.pc] & 0xFC000000)>> 26)

#unsigned_int = 32769

#signed_int = ctypes.c_int16(unsigned_int).value
#print(signed_int)

