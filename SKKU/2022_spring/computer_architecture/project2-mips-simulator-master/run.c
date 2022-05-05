/***************************************************************/
/*                                                             */
/*   MIPS-32 Instruction Level Simulator                       */
/*                                                             */
/*   CS311 KAIST                                               */
/*   run.c                                                     */
/*                                                             */
/***************************************************************/

#include <stdio.h>

#include "util.h"
#include "run.h"

/***************************************************************/
/*                                                             */
/* Procedure: get_inst_info                                    */
/*                                                             */
/* Purpose: Read insturction information                       */
/*                                                             */
/***************************************************************/
instruction* get_inst_info(uint32_t pc) 
{ 
    return &INST_INFO[(pc - MEM_TEXT_START) >> 2];
}

/***************************************************************/
/*                                                             */
/* Procedure: process_instruction                              */
/*                                                             */
/* Purpose: Process one instrction                             */
/*                                                             */
/***************************************************************/
void process_instruction(){
	/** Implement this function */
    // Get instruction of this cycle
    instruction* instr;
    instr = get_inst_info(CURRENT_STATE.PC);

    // Get deparsed format of instruction
    int opcode = instr->opcode;
    int rs = instr->r_t.r_i.rs;
    int rt = instr->r_t.r_i.rt;
    int rd = instr->r_t.r_i.r_i.r.rd;
    int shamt = instr->r_t.r_i.r_i.r.shamt;
    int funct = instr->func_code;
    int immed = instr->r_t.r_i.r_i.imm;
    int addr = instr->r_t.target;
    int index = instr->value;
    int instr_count; // check for RUN_BIT

    // Increase PC by 4
    CURRENT_STATE.PC += 4;
    
    // Execute instruction
    /* R format */
    if (opcode == 0x00) {
        if (funct == 0x21) { // ADDU
            CURRENT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
        } else if (funct == 0x24) { // AND
            CURRENT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] & CURRENT_STATE.REGS[rt];
        } else if (funct == 0x08) { // JR
            CURRENT_STATE.PC = CURRENT_STATE.REGS[rs];
        } else if (funct == 0x27) { // NOR
            CURRENT_STATE.REGS[rd] = ~(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]);
        } else if (funct == 0x25) { // OR
            CURRENT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt];
        } else if (funct == 0x2b) { // SLTU
            CURRENT_STATE.REGS[rd] = (CURRENT_STATE.REGS[rs] < CURRENT_STATE.REGS[rt]) ? 1 : 0;
        } else if (funct == 0x00) { // SLL
            CURRENT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << shamt;
        } else if (funct == 0x02) { // SRL
            CURRENT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> shamt;
        } else if (funct == 0x23) { // SUBU
            CURRENT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
        }
    }

    /* J format */
    if (opcode == 0x02) { // J
        CURRENT_STATE.PC = addr * 4;
    } else if (opcode == 0x03) { // JAL
        CURRENT_STATE.REGS[31] = CURRENT_STATE.PC; // 4 added
        CURRENT_STATE.PC = addr * 4;
    }

    /* I format */
	if (opcode == 0x09){ // ADDIU
		CURRENT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + immed;
	} else if (opcode == 0x0c) { // ANDI
		CURRENT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] & immed;
	} else if (opcode == 0x04) { // BEQ
		if (CURRENT_STATE.REGS[rs] == CURRENT_STATE.REGS[rt]) CURRENT_STATE.PC = CURRENT_STATE.PC + immed*4;
	} else if (opcode == 0x05) { // BNE
		if (CURRENT_STATE.REGS[rs] != CURRENT_STATE.REGS[rt]) CURRENT_STATE.PC = CURRENT_STATE.PC + immed*4;
	} else if (opcode == 0x0f) { // LUI
		CURRENT_STATE.REGS[rt] = immed << 16;
	} else if (opcode == 0x23) { // LW
		CURRENT_STATE.REGS[rt] = mem_read_32(CURRENT_STATE.REGS[rs] + immed);
	} else if (opcode == 0x0d) { // ORI
		CURRENT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] | immed;
	} else if (opcode == 0x0b) { // SLTIU
		if (CURRENT_STATE.REGS[rs] < immed) CURRENT_STATE.REGS[rt] = 1;
	    else CURRENT_STATE.REGS[rt] = 0;
	} else if (opcode == 0x2b) { // SW
		mem_write_32(CURRENT_STATE.REGS[rs] + immed, CURRENT_STATE.REGS[rt]);
	}

    // Set RUN_BIT to false when every instr is executed
    instr_count = (int)(CURRENT_STATE.PC - MEM_TEXT_START)/4;
    if (instr_count >= NUM_INST) {
        RUN_BIT = FALSE;
    }
}
