
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <stdint.h>

#include "definitions.hpp"

class Disassembler {
public:
    uint32_t instruction;
    char *buf;

    Disassembler() {}
    
    void fromBuffer(char *buffer, bool is_little_endian = true) {
        buf = buffer;
        int offset = is_little_endian ? 1 : -1;
        instruction = 0;
        for (int i = (int)(1.5-1.5*offset); 0<=i && i<=3; i+=offset) {
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
    uint16_t _getImmediate() { return instruction & 65535; }
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
    };