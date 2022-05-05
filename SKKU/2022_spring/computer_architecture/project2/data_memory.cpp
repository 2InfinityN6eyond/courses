#include "data_memory.hpp"

DataMemory::DataMemory() : Memory(
    (uint32_t)0x10000000,
    (uint32_t)0x10000
) {}