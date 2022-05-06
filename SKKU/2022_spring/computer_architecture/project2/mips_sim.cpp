
#include "mips_sim.hpp"

MipsSim::MipsSim(
    int n_insts,
    //RegisterSet register_set,
    InstMemory  inst_memory,
    DataMemory  data_memory
) {
    //this->register_set = register_set;
    this->inst_memory = inst_memory;
    this->data_memory = data_memory;
    printf("simulator constructed");

    register_set = RegisterSet{};


}

// : register_set(register_set), inst_memory(inst_memory), data_memory(data_memory) {
//    printf("simulator constructed");
//}

int MipsSim::run() {
    for (int i = 0; i < n_insts; i++) {
        
    }
}

int MipsSim::step() {
    // read PC value from instruction memory

    // fetch instruction and get rs rt rd
}


void MipsSim::printInstruction(int dix) {
    
}


void MipsSim::printState() {
    // print register
    

    // print instruction memory


    // print data memeory


}