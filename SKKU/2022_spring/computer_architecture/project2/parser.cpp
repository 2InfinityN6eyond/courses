#include <unistd.h>

class Parser {
  public:
    int fd;

    Parser(int fd) : fd(fd) {}

    int readLine(std::string &str) {
        char c;
        int len = 0;
        while (read(fd, &c, 1) == 1) {
            if (c == '\n') 
                return len;
            str.push_back(c);
            len++;
        }
        if (len == 0)
            return -1;
        return len;
    }

    int read4Bytes(std::string &str) {
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
};