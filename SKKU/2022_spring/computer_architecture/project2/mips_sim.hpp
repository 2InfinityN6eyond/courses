#ifndef MIPS_SIM_HPP
#define MIPS_SIM_HPP

#include <stdint.h>

#include "definitions.hpp"
#include "register_set.hpp"
#include "inst_memory.hpp"
#include "data_memory.hpp"

#include "decoder.hpp"

class MipsSim {
    public:
    MipsSim(
        int n_insts,
        InstMemory  inst_memory,
        DataMemory  data_memory
    );


    Disassembler ddd(18);


    void decode(int idx) {

        inst_memory.readWord(idx, &(ddd.instruction));
        ddd.disassemble();
    }

    int run();
    int step();

    void decomposeInst();

    int getPc(uint32_t *pc);
    int getOpcode(uint32_t *opcode);
    int getNewPC(uint32_t *new_pc);

    void printInstruction(int idx);


    void printState();

    private:
    int  n_insts;
    RegisterSet register_set;
    InstMemory  inst_memory;
    DataMemory  data_memory;

    uint32_t curr_instr;
    uint32_t RS, RD, RT;
    uint32_t immediate;
    uint32_t jump_addr;
    uint32_t brch_addr;
    uint32_t new_addr; 
};

#endif