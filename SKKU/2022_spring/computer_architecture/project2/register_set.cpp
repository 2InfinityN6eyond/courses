#include <stdint.h>
#include <strings.h>
#include <iostream>

#include "register_set.hpp"


RegisterSet::RegisterSet() : reg_write(false) {
    for (int i = 0; i < len; i++) {
        data[i] = 0;
    }
}

void RegisterSet::setRegWrite(bool RegWrite) { reg_write = RegWrite; }

uint32_t RegisterSet::read(int idx) {
    if (idx < 0 || idx > 32) {
        return NULL;
    } else {
        return data[idx];
    }
}

void RegisterSet::write(int idx, uint32_t val) {
    if (reg_write) {
        data[idx] = val;
    }
}



/*
RegisterSetSetterProxy::RegisterSetSetterProxy(
    RegisterSet register_set_,
    int idx_
) : register_set(register_set_), idx(idx_) {}
    
RegisterSetSetterProxy& RegisterSetSetterProxy::operator=(uint32_t value) {
    if (register_set.RegWrite)
        register_set.registers[idx] = value;
    return *this;
}


RegisterSet::RegisterSet() {
    bzero((void*)registers, sizeof(registers));
};

uint32_t RegisterSet::operator[](int idx) const {
    if (idx < 33) {
        return registers[idx];
    } else {
        std::cerr << "register index out of range" << std::endl;
        exit(-1);
    }
}

RegisterSetSetterProxy RegisterSet::operator[](int idx) {
    return RegisterSetSetterProxy(*this, idx);
}

int main() {
    RegisterSet register_set{};
    for (int i = 0; i < 32; i++) {
        register_set[i] = i + 1;
    }
    for (int i = 0; i < 32; i++) {
        std::cout << register_set.registers[i] << " ";
    }
}
*/

/*
class RegisterSetSetterProxy {
    public:

    RegisterSet& register_set;
    int idx;

    RegisterSetSetterProxy(
        RegisterSet register_set_,
        int idx_
    ) : register_set(register_set_), idx(idx_) {}

    RegisterSetSetterProxy & operator=(uint32_t value) {
        if (register_set.RegWrite)
            register_set.registers[idx] = value;
        return *this;
    }
};

class RegisterSet {
    public:

    bool RegWrite;

    // register is storing just raw data,
    // so simulated registers are considered unsigned

    // register $0  $31   $32 == PC
    uint32_t registers[33];

    RegisterSet() {
        bzero((void*)registers, sizeof(registers));
    };


    // overload bracket operater as getter and setter
    // setter set register $idx only if this->RegWrite == true
    uint32_t operator[](int idx) const {
        if (idx < 33) {
            return registers[idx];
        } else {
            std::cerr << "register index out of range" << std::endl;
            exit(-1);
        }
    }

    RegisterSetSetterProxy operator[](int idx) {
        return RegisterSetSetterProxy(*this, idx);
    }
};
*/
