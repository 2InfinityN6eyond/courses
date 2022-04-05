#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#define BUFLEN 256

enum mips_op_code {
    R_OPS   = 0X0,

    J       = 0x2,
    JAL     = 0x3,

    BEQ     = 0x4,
    BNE     = 0x5,
    ADDI    = 0x8,
    ADDIU   = 0x9,
    SLTI    = 0xa,
    SLTIU   = 0xb,
    ANDI    = 0xc,
    ORI     = 0xd,
    XORI    = 0xe,
    LUI     = 0xf,

    LB      = 0x20,
    LH      = 0x21,
    LW      = 0x23,
    LBU     = 0x24,
    LHU     = 0x25,
    SB      = 0x28,
    SH      = 0x29,
    SW      = 0x2b,
};

enum mips_funct_code {
    SLL     = 0x0,
    SRL     = 0x2,
    SRA     = 0x3,
    SLLV    = 0x4,
    SRLV    = 0x6,
    SRAV    = 0x7,
    JR      = 0x8,
    JALR    = 0x9,
    SYSCALL = 0xc,
    MFHI    = 0x10,
    MTHI    = 0x11,
    MFLO    = 0x12,
    MTLO    = 0x13,
    MULT    = 0x18,
    MULTU   = 0x19,
    DIV     = 0X1A,
    DIVU    = 0X1B,
    ADD     = 0x20,
    ADDU    = 0x21,
    SUB     = 0x22,
    SUBU    = 0x23,
    AND     = 0x24,
    OR      = 0x25,
    XOR     = 0x26,
    NOR     = 0x27,
    SLT     = 0x2a,
    SLTU    = 0x2b
};

class Disassembler {
public:
    int idx;
    uint32_t instruction;
    char *buf;

    Disassembler() { idx = 0; }
    
    void fromBuffer(char *buffer, bool is_little_endian = true) {
        buf = buffer;
        int offset = is_little_endian ? 1 : -1;
        instruction = 0;
        for (int i = (int)(1.5-1.5*offset); 0<=i&&i<=3; i+=offset) {
           instruction *= 256;
           instruction += (uint8_t)buffer[i];
        } 
    }

    uint32_t _getOpCode()    { return instruction >> 26; }
    uint32_t _getRS()        { return (instruction & 0x3e00000) >> 21; }
    uint32_t _getRT()        { return (instruction & 0x1f0000)  >> 16; }
    uint32_t _getRD()        { return (instruction & 0xf800)    >> 11; }
    uint32_t _getShamt()     { return (instruction & 0x7c0)     >> 6;}
    uint32_t _getFuncCode()  { return instruction & 63; }
    int16_t _getImmediate() { return instruction & 65535; }
    uint32_t _getAddress()   { return instruction & 67108863; }


    void printToLower(std::string str) {
        std::for_each(
            str.begin(),
            str.end(),
            [] (char c) -> void {
                if ('A' <= c && c <= 'Z')
                    printf("%c", c - 'A' + 'a');
            } 
        );
    }

    void _disassembleRtype() {
        switch (_getFuncCode())
        {
            
            case SLL     : 
                printToLower("SLL    ");
                std::cout<< " $" << _getRD() << ", $" << _getRT() << ", " << _getShamt()<< std::endl;
                break; 
            case SRL     : 
                printToLower("SRL    ");
                std::cout<< " $" << _getRD() << ", $" << _getRT() << ", " << _getShamt()<< std::endl;
                break; 
            case SRA     : 
                printToLower("SRA    ");
                std::cout<< " $" << _getRD() << ", $" << _getRT() << ", " << _getShamt()<< std::endl;
                break; 
            case SLLV    : 
                printToLower("SLLV   ");
                std::cout<< " $" << _getRD() << ", $" << _getRT() << ", " << _getShamt()<< std::endl;
                break; 
            case SRLV    : 
                printToLower("SRLV   ");
                std::cout<< " $" << _getRD() << ", $" << _getRT() << ", " << _getShamt()<< std::endl;
                break; 
            case SRAV    : 
                printToLower("SRAV   ");
                std::cout<< " $" << _getRD() << ", $" << _getRT() << ", $" << _getRS() << std::endl;
                break; 
            case JR      : 
                printToLower("JR     ");
                std::cout << " $" << _getRS() << std::endl;
                break; 
            case JALR    : 
                printToLower("JALR   ");
                std::cout << " $" << _getRD() <<  ", $" << _getRS() << std::endl;
                break; 
            case SYSCALL : 
                printToLower("SYSCALL");
                std::cout << std::endl;
                break; 
            case MFHI    : 
                printToLower("MFHI   ");
                std::cout << " $" << _getRD() << std::endl;
                break; 
            case MTHI    : 
                printToLower("MTHI   ");
                std::cout << " $" << _getRS()<< std::endl;
                break; 
            case MFLO    : 
                printToLower("MFLO   ");
                std::cout << " $" << _getRD()<< std::endl;
                break; 
            case MTLO    : 
                printToLower("MTLO   ");
                std::cout << " $" << _getRS()<< std::endl;
                break; 
            case MULT    : 
                printToLower("MULT   ");
                std::cout << " $" << _getRS() << ", $" << _getRT() << std::endl;
                break; 
            case MULTU   : 
                printToLower("MULTU  ");
                std::cout << " $" << _getRS() << ", $" << _getRT() << std::endl;
                break; 
            case DIV     : 
                printToLower("DIV    ");
                std::cout << " $" << _getRS() << ", $" << _getRT() << std::endl;
                break; 
            case DIVU    : 
                printToLower("DIVU   ");
                std::cout << " $" << _getRS() << ", $" << _getRT() << std::endl;
                break; 
            case ADD     : 
                printToLower("ADD    ");
                std::cout<< " $" << _getRD() << ", $" << _getRS() << ", $" << _getRT()<< std::endl;
                break; 
            case ADDU    : 
                printToLower("ADDU   ");
                std::cout<< " $" << _getRD() << ", $" << _getRS() << ", $" << _getRT()<< std::endl;
                break; 
            case SUB     : 
                printToLower("SUB    ");
                std::cout<< " $" << _getRD() << ", $" << _getRS() << ", $" << _getRT()<< std::endl;
                break; 
            case SUBU    : 
                printToLower("SUBU   ");
                std::cout<< " $" << _getRD() << ", $" << _getRS() << ", $" << _getRT()<< std::endl;
                break; 
            case AND     : 
                printToLower("AND    ");
                std::cout<< " $" << _getRD() << ", $" << _getRS() << ", $" << _getRT()<< std::endl;
                break; 
            case OR      : 
                printToLower("OR     ");
                std::cout<< " $" << _getRD() << ", $" << _getRS() << ", $" << _getRT()<< std::endl;
                break; 
            case XOR     : 
                printToLower("XOR    ");
                std::cout<< " $" << _getRD() << ", $" << _getRS() << ", $" << _getRT()<< std::endl;
                break; 
            case NOR     : 
                printToLower("NOR    ");
                std::cout<< " $" << _getRD() << ", $" << _getRS() << ", $" << _getRT()<< std::endl;
                break; 
            case SLT     : 
                printToLower("SLT    ");
                std::cout<< " $" << _getRD() << ", $" << _getRS() << ", $" << _getRT()<< std::endl;
                break;
            case SLTU    : 
                printToLower("SLTU   ");
                std::cout<< " $" << _getRD() << ", $" << _getRS() << ", $" << _getRT()<< std::endl;
                break; 
            default:
                std::cout << "unknown instruction" << std::endl;
                return;
                break;
            
        }
    }

    void _disassembleItype() {
        switch (_getOpCode())
        {
            case BEQ     :
                printToLower("BEQ  ");
                std::cout << " $" << _getRS() << ", $" << _getRT() << ", " << _getImmediate() << std::endl;
                break;
            case BNE     :
                printToLower("BNE  ");
                std::cout << " $" << _getRS() << ", $" << _getRT() << ", " << _getImmediate() << std::endl;
                break;
            case ADDI    :
                printToLower("ADDI ");
                std::cout << " $" << _getRT() << ", $" << _getRS() << ", " << _getImmediate() << std::endl;
                break;
            case ADDIU   :
                printToLower("ADDIU");
                std::cout << " $" << _getRT() << ", $" << _getRS() << ", " << _getImmediate() << std::endl;
                break;
            case SLTI    :
                printToLower("SLTI ");
                std::cout << " $" << _getRT() << ", $" << _getRS() << ", " << _getImmediate() << std::endl;
                break;
            case SLTIU   :
                printToLower("SLTIU");
                std::cout << " $" << _getRT() << ", $" << _getRS() << ", " << _getImmediate() << std::endl;
                break;
            case ANDI    :
                printToLower("ANDI ");
                std::cout << " $" << _getRT() << ", $" << _getRS() << ", " << _getImmediate() << std::endl;
                break;
            case ORI     :
                printToLower("ORI  ");
                std::cout << " $" << _getRT() << ", $" << _getRS() << ", " << _getImmediate() << std::endl;
                break;
            case XORI    :
                printToLower("XORI ");
                std::cout << " $" << _getRT() << ", $" << _getRS() << ", " << _getImmediate() << std::endl;
                break;
            case LUI     :
                printToLower("LUI  ");
                std::cout << " $" << _getRT() << ", " << _getImmediate() << std::endl;
                break;
            case LB      :
                printToLower("LB   ");
                std::cout << " $" << _getRT() << ", " << _getImmediate() << "($" << _getRS() << ")" << std::endl;
                break;
            case LH      :
                printToLower("LH   ");
                std::cout << " $" << _getRT() << ", " << _getImmediate() << "($" << _getRS() << ")" << std::endl;
                break;
            case LW      :
                printToLower("LW   ");
                std::cout << " $" << _getRT() << ", " << _getImmediate() << "($" << _getRS() << ")" << std::endl;
                break;
            case LBU     :
                printToLower("LBU  ");
                std::cout << " $" << _getRT() << ", " << _getImmediate() << "($" << _getRS() << ")" << std::endl;
                break;
            case SB      :
                printToLower("SB   ");
                std::cout << " $" << _getRT() << ", " << _getImmediate() << "($" << _getRS() << ")" << std::endl;
                break;
            case SH      :
                printToLower("SH   ");
                std::cout << " $" << _getRT() << ", " << _getImmediate() << "($" << _getRS() << ")" << std::endl;
                break;
            case SW      :
                printToLower("SW   ");
                std::cout << " $" << _getRT() << ", " << _getImmediate() << "($" << _getRS() << ")" << std::endl;
                break;
            case LHU     :
                printToLower("LHU  ");
                std::cout << " $" << _getRT() << ", " << _getImmediate() << "($" << _getRS() << ")" << std::endl;
                break;
            default:
                std::cout << "unknown instruction" << std::endl;
                return;
                break;
            
        }
    }

    void _disassembleJtype() {
        switch (_getOpCode())
        {
            case J    :
                printToLower("J  "); break;
            case JAL  :
                printToLower("JAL"); break;
        
            default:
                break;
        }
        std::cout << " " << _getAddress() << std::endl;        
    }

    void printBuffer() {
        for (int i = 0; i < 4; i++) {
            unsigned char c = (unsigned char)buf[i];
            printf("%c", c / 16 > 9 ? c / 16 - 10 + 'a' : c / 16 + '0');
            printf("%c", c % 16 > 9 ? c % 16 - 10 + 'a' : c % 16 + '0');
        }
    }
    
    void disassemble() {
        std::cout << "inst " << idx++ << ": ";
        printBuffer();
        printf(" ");
        switch (_getOpCode()) {
            case R_OPS :
                _disassembleRtype();
                break;
            case J :
                _disassembleJtype();
                break;
            case JAL :
                _disassembleJtype();
                break;
            default :
                _disassembleItype();
        }
    }
};

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
    Disassembler disassembler;


    std::string str; 
    while (parser.read4Bytes(str) > 0) {
        disassembler.fromBuffer((char *)str.c_str());                
        //std::cout << std::hex << disassembler._getOpCode() << " " << disassembler._getFuncCode() << std::endl;
        disassembler.disassemble();
        str.clear();
    }
}
