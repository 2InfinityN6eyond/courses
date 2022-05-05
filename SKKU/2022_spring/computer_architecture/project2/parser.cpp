#include <unistd.h>
#include "parser.hpp"

Parser::Parser(int fd) : fd(fd) {}

int Parser::read4Bytes(std::string &str) {
    char c;
    int len = 0;
    for (int i = 0; i < 4; i++) {
        if (read(fd, &c, 1) != 1)
            break;
        str.push_back(c);
        len++;
    }
    if (!len)
        return -1;
    return len;
}