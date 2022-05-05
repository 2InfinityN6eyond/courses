#include <stdint.h>
#include <strings.h>
#include <iostream>

#include "register_set.hpp"

RegisterSet::RegisterSet() {
    _data = new uint32_t[NUM_REGISTERS];
    for (int i = 0; i < NUM_REGISTERS; i++) {
        _data[i] = 0;
    }
}

RegisterSet::~RegisterSet() {
    delete[] _data;
}

RegisterSet::read(uint32_t idx, uint32_t *data) {
    if (idx < 0 || idx >= NUM_REGISTERS) {
        std::cerr << "invalid register access. tried to access register $" << idx << std::endl;
        return 0;
    }
    *data = _data[idx];
    return 1;
}

RegisterSet::write(uint32_t idx, uint32_t *data) {
    if (idx < 0 || idx >= NUM_REGISTERS) {
        std::cerr << "invalid register access. tried to access register $" << idx << std::endl;
        return 0;
    }
    _data[idx] = *data;
    return 1;
}