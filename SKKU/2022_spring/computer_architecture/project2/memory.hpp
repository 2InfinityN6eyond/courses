#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <stdint.h>
#include <vector>

class Memory {
    public:

    Memory(
        uint32_t outer_addr_ofst,
        uint32_t addr_space_size,
        bool computer_is_little_endian = true
    );
    
    Memory(
        uint32_t outer_addr_ofst,
        uint32_t addr_space_size,
        std::vector<uint8_t> buf,
        bool computer_is_little_endian = true
    );

    int setDataBuffer(std::vector<uint8_t> &buf);

    int  readBytes(uint32_t idx, uint32_t size, uint8_t *data);
    int writeBytes(uint32_t idx, uint32_t size, uint8_t *data);

    int  readWord(uint32_t idx, uint32_t *data);
    int writeWord(uint32_t idx, uint32_t *data);

    void printMemory(int num = -1);

    protected:
    bool computer_is_little_endian;
    std::vector<uint8_t> _data;
    uint32_t outer_addr_ofst; // subtracted to access real inner data buffer.
    uint32_t addr_space_size;

};

#endif