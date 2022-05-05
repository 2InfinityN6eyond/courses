#ifndef DEFINITIONS_H
#define DEFINITIONS_H

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

#endif