#ifndef REGISTER_SET
#define REGISTER_SET


#include <stdint.h>
#include <strings.h>
#include <iostream>

#define PC 32
#define NUM_REGISTERS 33

class RegisterSet {
    public:

    RegisterSet();
    ~RegisterSet();

    int  read(uint32_t idx, uint32_t *data);
    int write(uint32_t idx, uint32_t *data);

    private:
    uint32_t *_data;
};

#endif