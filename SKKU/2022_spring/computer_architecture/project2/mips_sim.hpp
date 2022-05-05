#ifndef MIPS_SIM_HPP
#define MIPS_SIM_HPP

#include "register_set.hpp"
#include "inst_memory.hpp"
#include "data_memory.hpp"

class MipsSim {
    public:
    MipsSim(
        int n_insts,
        RegisterSet register_set,
        InstMemory  inst_memory,
        DataMemory  data_memory
    );

    int run();
    int step();

    int getPc(uint32 *pc);
    int getOpcode(uint32_t *opcode);
    int getNewPC(uint32_t *new_pc);

    private:
    int  n_insts;
    RegisterSet register_set;
    InstMemory  inst_memory;
    DataMemory  data_memory;
};


#endif