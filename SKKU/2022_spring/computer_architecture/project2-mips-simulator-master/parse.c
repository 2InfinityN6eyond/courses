/***************************************************************/
/*                                                             */
/*   MIPS-32 Instruction Level Simulator                       */
/*                                                             */
/*   CS311 KAIST                                               */
/*   parse.c                                                   */
/*                                                             */
/***************************************************************/

#include <stdio.h>
#include <stdbool.h>

#include "util.h"
#include "parse.h"

int text_size;
int data_size;

instruction parsing_instr(const char *buffer, const int index)
{
    instruction instr;
	/** Implement this function */
	// Define basic formats
	char *opcode = malloc(6);
	char *rs = malloc(5);
	char *rt = malloc(5);
	char *rd = malloc(5);
	char *shamt = malloc(5);
	char *funct = malloc(6);
	char *immed = malloc(16); // for I
	char *addr = malloc(26); // for J

	// Check format type
	bool check_R = false;
	bool check_I = false;
	bool check_J = false;
	for (int i = 0; i < 6; i++) {
		opcode[i-0] = buffer[i];
	}
	int op_val = fromBinary(opcode);
	if (op_val == 0) check_R = true;
	else if (op_val == 2 || op_val == 3) check_J = true;
	else check_I = true;

	// Parse each type
	if (!check_J) { // R & I type
		for (int i = 6; i < 11; i++) {
			rs[i-6] = buffer[i];
		} for (int i = 11; i < 16; i++) {
			rt[i-11] = buffer[i];
		}
		if (check_R) { // R type
			for (int i = 16; i < 21; i++) {
				rd[i-16] = buffer[i];
			} for (int i = 21; i < 26; i++) {
				shamt[i-21] = buffer[i];
			} for (int i = 26; i < 32; i++) {
				funct[i-26] = buffer[i];
			}
				} else { // I type
			for (int i = 16; i < 32; i++) {
				immed[i-16] = buffer[i];
			}
		}
	} else { // J type
		for (int i = 6; i < 32; i++) {
			addr[i-6] = buffer[i];
		}
	}

	// Allocate each type
	instr.opcode = fromBinary(opcode);
	if (check_R) instr.func_code = fromBinary(funct);
	if (!check_J) {
		instr.r_t.r_i.rs = fromBinary(rs);
		instr.r_t.r_i.rt = fromBinary(rt);
		if (check_R) {
			instr.r_t.r_i.r_i.r.rd = fromBinary(rd);
			instr.r_t.r_i.r_i.r.shamt = fromBinary(shamt);
		} else {
			instr.r_t.r_i.r_i.imm = fromBinary(immed);
		}
	} else {
		instr.r_t.target = (uint32_t)fromBinary(addr);
	}
	instr.value = (uint32_t)index;

	// Return result
	return instr;
}

void parsing_data(const char *buffer, const int index)
{
	/** Implement this function */
	// Define data
	char *data = malloc(32);

	// Parse data
	for (int i = 0; i < 32; i++) {
		data[i-0] = buffer[i];
	}
	uint32_t data_val = (uint32_t)fromBinary(data);

	// Write data into the simulated memory
	/* Data section loaded from the address 0x10000000 */
	uint32_t addr = MEM_DATA_START + (uint32_t)index;
	mem_write_32(addr, data_val);

}

void print_parse_result()
{
    int i;
    printf("Instruction Information\n");

    for(i = 0; i < text_size/4; i++)
    {
	printf("INST_INFO[%d].value : %x\n",i, INST_INFO[i].value);
	printf("INST_INFO[%d].opcode : %d\n",i, INST_INFO[i].opcode);

	switch(INST_INFO[i].opcode)
	{
	    //Type I
	    case 0x9:		//(0x001001)ADDIU
	    case 0xc:		//(0x001100)ANDI
	    case 0xf:		//(0x001111)LUI	
	    case 0xd:		//(0x001101)ORI
	    case 0xb:		//(0x001011)SLTIU
	    case 0x23:		//(0x100011)LW	
	    case 0x2b:		//(0x101011)SW
	    case 0x4:		//(0x000100)BEQ
	    case 0x5:		//(0x000101)BNE
		printf("INST_INFO[%d].rs : %d\n",i, INST_INFO[i].r_t.r_i.rs);
		printf("INST_INFO[%d].rt : %d\n",i, INST_INFO[i].r_t.r_i.rt);
		printf("INST_INFO[%d].imm : %d\n",i, INST_INFO[i].r_t.r_i.r_i.imm);
		break;

    	    //TYPE R
	    case 0x0:		//(0x000000)ADDU, AND, NOR, OR, SLTU, SLL, SRL, SUBU  if JR
		printf("INST_INFO[%d].func_code : %d\n",i, INST_INFO[i].func_code);
		printf("INST_INFO[%d].rs : %d\n",i, INST_INFO[i].r_t.r_i.rs);
		printf("INST_INFO[%d].rt : %d\n",i, INST_INFO[i].r_t.r_i.rt);
		printf("INST_INFO[%d].rd : %d\n",i, INST_INFO[i].r_t.r_i.r_i.r.rd);
		printf("INST_INFO[%d].shamt : %d\n",i, INST_INFO[i].r_t.r_i.r_i.r.shamt);
		break;

    	    //TYPE J
	    case 0x2:		//(0x000010)J
	    case 0x3:		//(0x000011)JAL
		printf("INST_INFO[%d].target : %d\n",i, INST_INFO[i].r_t.target);
		break;

	    default:
		printf("Not available instruction\n");
		assert(0);
	}
    }

    printf("Memory Dump - Text Segment\n");
    for(i = 0; i < text_size; i+=4)
	printf("text_seg[%d] : %x\n", i, mem_read_32(MEM_TEXT_START + i));
    for(i = 0; i < data_size; i+=4)
	printf("data_seg[%d] : %x\n", i, mem_read_32(MEM_DATA_START + i));
    printf("Current PC: %x\n", CURRENT_STATE.PC);
}
