#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <vector>

#include "parser.hpp"
#include "register_set.hpp"
#include "inst_memory.hpp"
#include "data_memory.hpp"
#include "mips_sim.hpp"

int main(int argc, char **argv) {

    int n_insts;

    //RegisterSet register_set{};
    InstMemory  inst_memory{};
    DataMemory  data_memory{};

    if (argc < 3) { // error guard
        std::cerr << 
        "usage: mips-sim [n_insts] [inst_path] [data_path]"
        << std::endl;
        
        return -1;
    }

    n_insts = atoi(argv[1]);
    
    int inst_fd = open(argv[2], O_RDONLY);
    if (inst_fd == -1) {
        std::cerr << "inst file open failed" << std::endl;
        return -1;
    }
    Parser inst_parser(inst_fd);
    std::vector<uint8_t> inst_buf;
    int inst_file_len = inst_parser.readFile(inst_buf);
    inst_memory.setDataBuffer(inst_buf);

    printf("inst read...\n");

    inst_memory.printMemory(inst_file_len);

    if (argc > 3) { // read data file
        int data_fd = open(argv[3], O_RDONLY);
        if (data_fd == -1) {
            std::cerr << "data file open failed" << std::endl;
            return -1;
        }
        Parser data_parser(data_fd);
        std::vector<uint8_t> data_buf;
        int data_file_len = data_parser.readFile(data_buf);
        data_memory.setDataBuffer(data_buf);

        printf("data read...\n");
        data_memory.printMemory(data_file_len);
    }


    uint32_t val;
    printf("\n%d  %x\n", inst_memory.readWord(1, &val), val);
    printf("\n%d  %x\n", data_memory.readWord(1 + 0x10000000, &val), val);

    printf("initializing simulator...\n");
    MipsSim(
        n_insts,
        //register_set,
        inst_memory,
        data_memory
    );

}