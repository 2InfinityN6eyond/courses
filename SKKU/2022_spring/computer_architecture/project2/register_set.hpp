#include <stdint.h>
#include <strings.h>
#include <iostream>

class RegisterSet;

class RegisterSetGetterProxy {
    public:

    RegisterSet& register_set;
    int idx;
    
    RegisterSetGetterProxy(RegisterSet register_set_, int idx_);
    RegisterSetGetterProxy & operator=(uint32_t value);
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
    RegisterSetGetterProxy operator[](int idx);
};