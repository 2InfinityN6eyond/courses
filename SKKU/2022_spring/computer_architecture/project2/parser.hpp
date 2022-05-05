#ifndef PARSER_HPP
#define PARSER_HPP

#include <unistd.h>

class Parser {
  public:
    int fd;

    Parser(int fd);
    int read4Bytes(std::string &str);
};

#endif