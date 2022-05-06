#include "inst_memory.hpp"

InstMemory::InstMemory() : Memory(
    (uint32_t)0x0,
    (uint32_t)0x10000
) {}


/*
InstMemory::InstMemory(
    uint32_t outer_addr_ofst,
    uint32_t addr_space_size,
    std::vector<uint32_t> instruction
) : Memory(outer_addr_ofst, addr_space_size) {
    _data; 
}
*/