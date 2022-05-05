#include <stdint.h>

#include "memory.hpp"

Memory::Memory(uint32_t outer_addr_ofst, uint32_t addr_space_size) {
    _data = new uint8_t[addr_space_size];
    for (int i = 0; i < addr_space_size; i++) {
        _data[i] = 0xFF;
    }
    outer_addr_ofst = outer_addr_ofst;
    addr_space_size = addr_space_size;
}

Memory::~Memory() {
    delete[] _data;
}

int Memory::read(uint32_t idx, uint32_t size, uint8_t *data) {
    int inner_idx = idx - outer_addr_ofst;
    if (size < 1) {
        return 0;
    
    if (inner_idx < 0 || inner_idx + size >= addr_space_size) {
        return 0;
    }
    for (int i = 0; i < size; i++) {
        data[i] = _data[i];
    }
    return 1;
}

int Memory::write(uint32_t idx, uint32_t size, uint8_t *data) {
    int inner_idx = idx - outer_addr_ofst;
    if (size < 1) {
        return 0;
    }
    if (inner_idx < 0 || inner_idx >= address_size) {
        return 0;
    }
    for (int i = 0; i < size; i++) {
        _data[i] = data[i];
    }
    return 1;
}