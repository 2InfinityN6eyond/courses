#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 256

class String {
public:
    char *buffer;
    int len, capacity;   

    String() : len(0), capacity(BUFLEN) {
        buffer = (char*)malloc(sizeof(char) * capacity + 1);
        bzero((void*)buffer, capacity);        
    }

    ~String() {
        free(buffer);
    }

    int append(char  val) {
        if (len == capacity) {
            char *new_buffer = (char*)malloc(sizeof(char) * (capacity * 2 + 1));
            //printf("new buffer : %p old : %p %s\n", new_buffer, buffer, buffer);
            if (! new_buffer) {
                return (0);
            }
            for (int i = 0; i < capacity; i++) {
                new_buffer[i] = buffer[i];
            }
            for (int i = capacity; i < capacity * 2 + 1; i++) {
                new_buffer[i] = 0;   
            }
            free(buffer);
            buffer = new_buffer;
            capacity = capacity * 2;
            //printf("buffer : %p %s\n\n", buffer, buffer);
        }
        buffer[len++] = val;
        return len;
    }
    
    void clear() {
        for (int i = 0; i < len; i++) {
            buffer[i] = 0;
        }
        len = 0;
    }

};

class Disassembler {
public:
    uint32_t * instruction;

    Disassembler() {}
    
    void readInstruction(, bool is_little_endian) {

    }

    void getOpcode()
}

class Parser {
  public:
    int fd;

    Parser(int fd) : fd(fd) {}

    int readLine(String &str) {
        char c;
        int len = 0;
        while (read(fd, &c, 1) == 1) {
            if (c == '\n') 
                return len;
            str.append(c);
            len++;
        }
        if (len == 0)
            return -1;
        return len;
    }
};

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: mips-sim [binary machine code file path]] ..." << std::endl;
        return -1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("file open failed\n");
        return -1;
    }

    Parser parser{fd};
    
    String str; 
    while (parser.readLine(str) > 0) {
        std::cout << str.buffer << std::endl;        
        str.clear();
    }
}
