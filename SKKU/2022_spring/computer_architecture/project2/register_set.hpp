#include <stdint.h>
#include <strings.h>
#include <iostream>

class RegisterSet {
    protected:

    bool reg_write;
    uint32_t data[33];

    public:

    RegisterSet();
    void setRegWrite(bool RegWrite);
    uint32_t read(int idx);
    void write(int idx, uint32_t val);

}


/*
class RegisterSet;

class RegisterSetSetterProxy {
    public:

    RegisterSet& register_set;
    int idx;
    
    RegisterSetSetterProxy(RegisterSet register_set_, int idx_);
    RegisterSetSetterProxy & operator=(uint32_t value);
};

class RegisterSet {
    public:

    bool RegWrite;

    // register is storing just raw data,
    // so simulated registers are considered unsigned

    // register $0  $31   $32 == PC
    uint32_t registers[33];

    RegisterSet();

    // overload bracket operater as getter and setter
    // setter set register $idx only if this->RegWrite == true
    uint32_t operator[](int idx) const;   
    RegisterSetSetterProxy operator[](int idx);
};
*/