#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <vector>

#include "parser.hpp"
#include "register_set.hpp"
#include "inst_memory.hpp"
#include "data_memory.hpp"

int main(int argc, char **argv) {

    int n_insts;

    RegisterSet register_set();
    InstMemory  inst_memory();
    DataMemory  data_memory();


    if (argc < 3) { //
        std::cerr << "usage: mips-sim [num of instructions to run] [instruction bin file path] [data bin file path]" << std::endl;
        return -1;
    }
    
    if (argc > 3) { // read data file
        int data_fd = open(argv[2], O_RDONLY);
        if (data_fd == -1) {
            std::cerr << "data bin file open failed" << std::endl;
            return -1;
        }
        Parser data_parser(data_fd);
        std::vector<uint8_t> data_buf;
        
        while (true) {

        }
    }

    n_insts = atoi(argv[1]);    
    
    int inst_fd = open(argv[2], O_RDONLY);
    if (inst_fd == -1) {
        std::cerr << "data bin file open failed" << std::endl;
        return -1;
    }
    Parser inst_parser(inst_fd)
    std::vector<uint8_t> inst_buf;

    for (int i = 0; i < n_insts; i++) {
        uint32_t inst_val = 0;
        inst_parser.read4Bytes(inst_buf);
        for (int j = 0; j < 4; j++) {
            // generate inst_val
        }
    }

    

}