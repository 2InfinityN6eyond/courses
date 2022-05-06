#include "parser.hpp"

Parser::Parser(
    int fd,
    bool computer_is_little_endian
) : fd(fd),
computer_is_little_endian(computer_is_little_endian) {}

int Parser::readWord(std::vector<uint8_t> &buf) {
    uint8_t c;
    int len = 0;
    for (int i = 0; i < 4; i++) {
        if (read(fd, &c, 1) != 1)
            break;
        buf.push_back(c);
        len++;
    }
    if (!len)
        return -1;
    return len;
}

int Parser::readFile(std::vector<uint8_t> &buf) {
    uint8_t c;
    int file_length = 0;
    while (read(fd, &c, 1) == 1) {
        //printf("%x ", c);
        buf.push_back(c);
        file_length++;
    }
    return file_length;
}

int Parser::parseInstFile(std::vector<uint32_t> &insts) {
    insts.clear();
    std::vector<uint8_t> buf;
    buf.clear();

    while (readWord(buf) == 4) {
        uint32_t inst = 0;
        int offset = computer_is_little_endian ? 1 : -1;

        for (int i = (int)(1.5-1.5*offset); 0<=i&&i<=3; i+=offset) {
            inst *= 256;
            inst += buf.at(i);
        } 

        insts.push_back(inst);
    }

    return 1;
}