#ifndef MIPS_SIM_HPP
#define MIPS_SIM_HPP

#include <stdint.h>

#include "register_set.hpp"
#include "inst_memory.hpp"
#include "data_memory.hpp"

class MipsSim {
    public:
    MipsSim(
        int n_insts,
        InstMemory  inst_memory,
        DataMemory  data_memory
    );

    int run();
    int step();

    int getPc(uint32_t *pc);
    int getOpcode(uint32_t *opcode);
    int getNewPC(uint32_t *new_pc);

    private:
    int  n_insts;
    RegisterSet register_set;
    InstMemory  inst_memory;
    DataMemory  data_memory;

    uint32_t RS, RD, RT;
    uint32_t immediate;
    uint32_t jump_addr;
    uint32_t brch_addr;
    uint32_t new_addr; 
};


#endif