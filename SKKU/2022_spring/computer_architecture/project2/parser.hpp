#ifndef PARSER_HPP
#define PARSER_HPP

#include <unistd.h>
#include <vector>
#include <stdint.h>

class Parser {
    public:
    int fd;

    Parser(
        int fd,
        bool computer_is_little_endian = true
    );

    int readWord(std::vector<uint8_t> &buf);
    int parseInstFile(std::vector<uint32_t> &insts);
    int readFile(std::vector<uint8_t> &buf);

    private:
    bool computer_is_little_endian;

};

#endif