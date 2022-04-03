#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <string>

#define BUFLEN 256

enum MIPS_IS {
    SLL = 0,
}

typedef struct Instruction32 {
    char *buffer;
    int getOp() {}
    int getRS() {}
    int getRT() {}
    int getRD() {}
    int getConst() {}
    int getShamt() {}
    int getFunct() {}
    void clear() {}
} Instruction32;

class Parser {
  public:
    int fd;
    char tmp;

    Parser(int fd) : fd(fd) {}

    int readLine(std::string str) {
        while (read(fd, &(str->last()), 1) == 1) {
            if (str->last() == '\n') 
                return 1;
        }
    }
};

class Disassembler {
  public :
    char system_is_big_endian;
    
    Disassembler() {}
    void disassembleLine() {}
};

int main(int argc, char **argv) {
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("file open failed\n");
        return -1;
    }
    Instruction32 instruction;
    Parser parser{fd};
    Disassembler disassembler();
    while (parser.readLine(instruction.buffer)) {
        disassembleLine(instruction);
        instruction.clear();
    }
}
