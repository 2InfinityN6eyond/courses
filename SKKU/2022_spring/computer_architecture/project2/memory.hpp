#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <stdint.h>

class Memory {
    public:

    Memory(uint32_t outer_addr_ofst, uint32_t addr_space_size);
    ~Memory();

    int  read(uint32_t idx, uint32_t size, uint8_t *data);
    int write(uint32_t idx, uint32_t size, uint8_t *data);

    private:
    uint8_t *_data;
    uint32_t outer_addr_ofst; // subtracted to access real inner data buffer.
    uint32_t addr_space_size;
}

#endif