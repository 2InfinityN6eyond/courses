#include <stdlib.h>

#define J 0x02
#define JAL 0x03
#define BEQ 0x04
#define BNE 0x05
#define ADDI 0x08
#define ADDIU 0x09
#define SLTI 0x0A
#define SLTIU 0x0B
#define ANDI 0x0C
#define ORI 0x0D
#define LUI 0x0F
#define LW 0x23
#define SW 0x2B
#define SLL 0x00
#define SRL 0x02
#define JR 0x08
#define SYSCALL 0x0C
#define ADD 0x20
#define ADDU 0x21
#define SUB 0x22
#define SUBU 0x23
#define AND 0x24
#define OR 0x25
#define SLT 0x2A
#define SLTU 0x2B

#define MAXBUF 65536
#define RESISTERNUM 32
#define BITMASK(n) ((1 << n) - 1)

typedef struct {
    int32_t target;
    int16_t imm;
	uint8_t op, rs, rt, rd, sa, funct;
} instruction;

typedef struct {
	char valid;
	char dirty;
	int tag;
	int data[1024]; // represents 1 block 
} cache;

static const char* OPCODE_INSTRUCTION_NAMES[64] =
{
	NULL, NULL, "j", "jal", "beq", "bne", NULL, NULL,
	"addi", "addiu", "slti", "sltiu", "andi", "ori", NULL, "lui",
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, "lw", NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, "sw", NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};



static const char* FUNCTION_INSTRUCTION_NAMES[64] =
{
	"sll", NULL, "srl", NULL , NULL, NULL, NULL, NULL,
	"jr", NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	"add", "addu", "sub", "subu", "and", "or", NULL,
	NULL, NULL, NULL, "slt", "sltu", NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

// no syscall anymore