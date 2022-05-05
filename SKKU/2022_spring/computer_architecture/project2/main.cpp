
#include <iostream>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char **argv) {

    int inst_fd;
    int data_fd;

    if (argc < 2) {
        std::cerr << "usage: mips-sim [num of instructions to run] [instruction bin file path] [data bin file path]" << std::endl;
        return -1;
    } else if (argc > 2) {
        data_fd = open(argv[2], O_RDONLY);
        if (data_fd == -1) {
            std::cerr << "data bin file open failed" << std::endl;
            return -1;
        }
    }
    inst_fd = open(argv[1], O_RDONLY);
}