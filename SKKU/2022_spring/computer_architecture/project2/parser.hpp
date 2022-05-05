#ifndef PARSER_HPP
#define PARSER_HPP

#include <unistd.h>
#include <vector>
#include <stdint.h>

class Parser {
  public:
    int fd;

    Parser(int fd);
    int read4Bytes(std::vector<uint8_t> buf);
};

#endif