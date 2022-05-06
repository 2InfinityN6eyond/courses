#include <stdint.h>
#include <stdio.h>

#include "memory.hpp"

Memory::Memory(
    uint32_t outer_addr_ofst,
    uint32_t addr_space_size,
    bool computer_is_little_endian
) : _data(addr_space_size, 0xFF),
    outer_addr_ofst(outer_addr_ofst),
    addr_space_size(addr_space_size),
    computer_is_little_endian(computer_is_little_endian) {}

Memory::Memory(
    uint32_t outer_addr_ofst,
    uint32_t addr_space_size,
    std::vector<uint8_t> buf,
    bool computer_is_little_endian
) : _data(addr_space_size, 0xFF),
    outer_addr_ofst(outer_addr_ofst),
    addr_space_size(addr_space_size),
    computer_is_little_endian(computer_is_little_endian) {
    for (int i = 0; i < buf.size(); i++) {
        _data.at(i) = buf.at(i);
    }
}


void Memory::printMemory(int num) {
    if (num < 0)
        num = _data.size();
    for (int i = 0; i < num; i++) {
        printf("%x ", _data.at(i));
    }
    printf("\n");
}

int Memory::setDataBuffer(std::vector<uint8_t> &buf) {
    if (buf.size() > _data.size()) {
        return 0;
    }
    for (int i = 0; i < buf.size(); i++) {
        _data.at(i) = buf.at(i);
    }
    return 1;
}

int Memory::readBytes(uint32_t idx, uint32_t size, uint8_t *data) {
    int inner_idx = idx - outer_addr_ofst;
    if (size < 1) {
        return 0;
    }
    
    if (inner_idx < 0 || inner_idx + size >= addr_space_size) {
        return 0;
    }
    for (int i = 0; i < size; i++) {
        data[i] = _data.at(i);
    }
    return 1;
}

int Memory::writeBytes(uint32_t idx, uint32_t size, uint8_t *data) {
    int inner_idx = idx - outer_addr_ofst;
    if (size < 1) {
        return 0;
    }
    if (inner_idx < 0 || inner_idx >= addr_space_size) {
        return 0;
    }
    for (int i = 0; i < size; i++) {
        _data.at(i) = data[i];
    }
    return 1;
}

int Memory::readWord(uint32_t idx, uint32_t *data) {
    int inner_idx = idx - outer_addr_ofst;
    //printf("outer_off:%d, inner_idx:%d\n", outer_addr_ofst, inner_idx);
    if (inner_idx < 0 || inner_idx + 4 >= addr_space_size) {
        return 0;
    }
    *data = 0;
    int offset = computer_is_little_endian ? 1 : -1;
    for (int i = (int)(1.5-1.5*offset); 0<=i&&i<=3; i+=offset) {
        *data *= 256;
        *data += _data.at(i + inner_idx);
    } 
    return 1;
}

int Memory::writeWord(uint32_t idx, uint32_t *data) {
    int inner_idx = idx - outer_addr_ofst;
    if (inner_idx < 0 || inner_idx + 4 >= addr_space_size) {
        return 0;
    }
    int offset = computer_is_little_endian ? -1 : 1;
    for (int i = (int)(1.5 - 1.5*offset); 0<=i&&i<=3; i+=offset) {
        _data.at(i + inner_idx) = *data % 256;
        *data /= 256;
    }
    return 1;
}