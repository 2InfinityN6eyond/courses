
#include "mips_sim.hpp"

MipsSim::MipsSim(
    int n_insts,
    RegisterSet register_set,
    InstMemory  inst_memory,
    DataMemory  data_memory
) : register_set(register_set), inst_memory(inst_memory), data_memory(data_memory) {}

int MipsSim::run() {
    for (int i = 0; i < n_insts; i++) {
        
    }
}

int MipsSim::step() {

}
