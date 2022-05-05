#include "parser.hpp"

Parser::Parser(int fd) : fd(fd) {}

int Parser::read4Bytes(std::vector<uint8_t> buf) {
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