#include <stdint.h>
#include <stdio.h>
#include "mips_simulator.h"
//#pragma warning(disable: 4996)

extern int g_total;
extern int g_hits;

extern int8_t g_cacheType;
extern cache g_cache[64];

extern int32_t* instMem;
extern int8_t* dataMem;

extern int32_t PC;
extern int32_t reg[RESISTERNUM];
extern instruction* inst;
extern int inst_count;
extern int LRU[16][4];


extern int cache1_off_bit_num;
extern int cache1_idx_bit_num;

extern int cache2_off_bit_num;
extern int cache2_idx_bit_num;

int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}


/* Open file, and save file data to mem, and close file */
void readFile(const char* fileName, void* mem, int8_t size) {
    FILE* fp;
    long int filesize;
    if (NULL == (fp = fopen(fileName, "rb"))) {
        printf("Can not open %s\n", fileName);
        exit(1);
    }

    fseek(fp, 0L, SEEK_END);
    filesize = ftell(fp);

    fseek(fp, 0L, SEEK_SET);
    fread(mem, size, filesize / size, fp);
    fclose(fp);
}

int32_t swap_int32(int32_t val) {
    val = ((val & 0x000000FF) << 24)
        | ((val & 0x0000FF00) << 8)
        | ((val & 0x00FF0000) >> 8)
        | ((val & 0xFF000000) >> 24);
    return val;
}

void instDecode(int32_t code) {
    inst->op = (code >> 26) & BITMASK(6);
    inst->rs = (code >> 21) & BITMASK(5);
    inst->rt = (code >> 16) & BITMASK(5);
    inst->rd = (code >> 11) & BITMASK(5);
    inst->sa = (code >> 6) & BITMASK(5);
    inst->funct = code & BITMASK(6);
    inst->imm = code & BITMASK(16);
    inst->target = code & BITMASK(26);
    if (inst->target >> 25) {
        inst->target |= 0xfc000000;
    }
}

int isValidInstruction() {
    const char* name;
    if (inst->op) {
        name = OPCODE_INSTRUCTION_NAMES[inst->op];
    } else {
        name = FUNCTION_INSTRUCTION_NAMES[inst->funct];
    }
    return (name != NULL);
}

void execution() {
    if (inst->op == 0)
        R_type();
    else
        I_type();
}

void R_type() {

    switch (inst->funct) {
    case SLL:
        reg[inst->rd] = reg[inst->rt] << inst->sa;
        break;
    case SRL:/* unsigned shift */
        if (inst->sa == 0)
            reg[inst->rd] = reg[inst->rt];
        else
            reg[inst->rd] = (reg[inst->rt] >> inst->sa) & ~(0xffffffff << (32 - inst->sa));
        break;
    case JR:
        PC = reg[inst->rs] / 4;
        break;
    case SYSCALL:
        switch (reg[2]) {
        case 1:
            printf("%d", reg[4]);
            break;
        case 4:
            printf("%s", dataMem + (reg[4] & 0x00FFFFFF));
            break;
        case 5:
            if (1 == scanf("%d", reg + 2))
                break;
            else {
                printf("Can not read integer from stdin\n");
                exit(1);
            }
        default:
            break;
        }
        break;
    case ADD:
        reg[inst->rd] = reg[inst->rs] + reg[inst->rt];
        break;
    case ADDU:
        reg[inst->rd] = reg[inst->rs] + reg[inst->rt];
        break;
    case SUB:
        reg[inst->rd] = reg[inst->rs] - reg[inst->rt];
        break;
    case SUBU:
        reg[inst->rd] = reg[inst->rs] - reg[inst->rt];
        break;
    case AND:
        reg[inst->rd] = reg[inst->rs] & reg[inst->rt];
        break;
    case OR:
        reg[inst->rd] = reg[inst->rs] | reg[inst->rt];
        break;
    case SLT:
        reg[inst->rd] = (reg[inst->rs] < reg[inst->rt]) ? 1 : 0;
        break;
    case SLTU:
        reg[inst->rd] = ((unsigned)reg[inst->rs] < (unsigned)reg[inst->rt]) ? 1 : 0;
        break;
    default:
        break;
    }
}

void I_type() 
{   
    uint32_t address;
    switch (inst->op) {
    case J:
        PC = (PC & 0xf0000000) | inst->target;
        break;
    case JAL:
        reg[31] = PC << 2;
        PC = (PC & 0xf0000000) | inst->target;
        break;
    case BEQ:
        if (reg[inst->rs] == reg[inst->rt])
            PC += inst->imm;
        break;
    case BNE:
        if (reg[inst->rs] != reg[inst->rt])
            PC += inst->imm;
        break;
    case ADDI:
        reg[inst->rt] = reg[inst->rs] + inst->imm;
        break;
    case ADDIU:
        reg[inst->rt] = (unsigned)reg[inst->rs] + (unsigned)inst->imm;
        break;
    case SLTI:
        reg[inst->rt] = (reg[inst->rs] < inst->imm) ? 1 : 0;
        break;
    case SLTIU:
        reg[inst->rt] = ((unsigned)reg[inst->rs] < (unsigned)inst->imm) ? 1 : 0;
        break;
    case ANDI:
        reg[inst->rt] = reg[inst->rs] & (inst->imm & 0x0000ffff);
        break;
    case ORI:
        reg[inst->rt] = reg[inst->rs] | (inst->imm & 0x0000ffff);
        break;
    case LUI:
        reg[inst->rt] = inst->imm << 16;
        break;
    case LW:
        address = 0x000FFFFF & (reg[inst->rs] + inst->imm);
        if (isLWHit(address)) g_hits++;
        g_total++;
        break;
    case SW:
        address = 0x000FFFFF & (reg[inst->rs] + inst->imm);
        if (isSWHit(address)) g_hits++;
        g_total++;
        break;
    default:
        break;
    }

}

int isLWHit(uint32_t address) {
    if (g_cacheType == 1) {
        //int tag = address >> 10;
        //int idx = (address >> 5) & BITMASK(5);
        //int off = address & BITMASK(5);

        int tag = address >> (cache1_off_bit_num + cache1_idx_bit_num);
        int idx = (address >> cache1_off_bit_num) & BITMASK(cache1_idx_bit_num);
        int off = address & BITMASK(cache1_off_bit_num);

        if ((g_cache[idx].valid == 1) && (g_cache[idx].tag == tag)) { // cache hit
            reg[inst->rt] = g_cache[idx].data[off / 4];
            return 1;
        }
        else {
            int start = address - off; // start of that block address
            g_cache[idx].valid = 1;
            g_cache[idx].tag = tag;
            for (int i = 0; i < (int)power(2, cache1_off_bit_num) / 4 ; i++) { // fill block into cache
                g_cache[idx].data[i] = swap_int32(*((int32_t*)(dataMem + start + i * 4)));
            }

            reg[inst->rt] = swap_int32(*((int32_t*)(dataMem + address)));
            return 0;
        }
    }
    else { // cache_type == 2
        //int tag = address >> 10;
        //int idx = (address >> 6) & BITMASK(4);
        //int off = address & BITMASK(6);

        int tag = address >> (cache2_off_bit_num + cache2_idx_bit_num);
        int idx = (address >> cache2_off_bit_num) & BITMASK(cache2_idx_bit_num);
        int off = address & BITMASK(cache2_off_bit_num);

        //for (int i = 0; i < 4; i++) {
        //    if ((g_cache[idx * 4 + i].valid == 1) && (g_cache[idx * 4 + i].tag == tag)) {
        //        reg[inst->rt] = g_cache[idx * 4 + i].data[off / 4];
        //        LRU[idx][i] = inst_count;
        //        return 1;
        //    }
        //}

        for (int i = 0; i < 2; i++) {
            if ((g_cache[idx * 2 + i].valid == 1) && (g_cache[idx * 2 + i].tag == tag)) {
                reg[inst->rt] = g_cache[idx * 2 + i].data[off / 4];
                LRU[idx][i] = inst_count;
                return 1;
            }
        }

        // cache miss

        idx = getIdx(idx);   // true cache perspective of idx to replace
        int start = address - off;
        g_cache[idx].valid = 1;
        g_cache[idx].tag = tag;
        for (int i = 0; i < (int)power(2, cache2_off_bit_num) / 4; i++) {
            g_cache[idx].data[i] = swap_int32(*((int32_t*)(dataMem + start + i * 4)));
        }

        reg[inst->rt] = swap_int32(*((int32_t*)(dataMem + address)));
        return 0;
    }

    return 1;
}

int getIdx(int idx)
{
    int min = LRU[idx][0];
    int min_idx = 0;
    for (int i = 1; i < 2; i++) {
        if (LRU[idx][i] < min) {
            min = LRU[idx][i];
            min_idx = i;
        }
    }
    LRU[idx][min_idx] = inst_count;
    return (idx * 2 + min_idx);
}

int isSWHit(uint32_t address) {
    if (g_cacheType == 1) {
        // write through, no write allocate
        // write hit  : update cache, set dirty bit
        // write miss : fetch the block, update cache, set dirty bit
        // dirty line replace : update memory

        //int tag = address >> 10;
        //int idx = (address >> 5) & BITMASK(5);
        //int off = address & BITMASK(5);

        int tag = address >> (cache1_off_bit_num + cache1_idx_bit_num);
        int idx = (address >> cache1_off_bit_num) & BITMASK(cache1_idx_bit_num);
        int off = address & BITMASK(cache1_off_bit_num);

        *(int32_t*)(dataMem + address) = swap_int32(reg[inst->rt]);
        if ((g_cache[idx].valid == 1) && (g_cache[idx].tag == tag)) {
            g_cache[idx].data[off / 4] = reg[inst->rt];
            return 1;
        }
        return 0;
    }
    else { // cache 2 write back -> update cache
        // write-back, write- allocate
        // write hit  : update cache, update memory
        // write miss : update memory
    
        //int tag = address >> 10;
        //int idx = (address >> 6) & BITMASK(4);
        //int off = address & BITMASK(6);

        int tag = address >> (cache2_off_bit_num + cache2_idx_bit_num);
        int idx = (address >> cache2_off_bit_num) & BITMASK(cache2_idx_bit_num);
        int off = address & BITMASK(cache2_off_bit_num);

        *(int32_t*)(dataMem + address) = swap_int32(reg[inst->rt]); // write to memory

        for (int i = 0; i < 2; i++) {
            if ((g_cache[idx * 2 + i].valid == 1) && (g_cache[idx * 2 + i].tag == tag)) {
                g_cache[idx * 2 + i].data[off / 4] = reg[inst->rt];
                LRU[idx][i] = inst_count;
                return 1;
            }
        }

        idx = getIdx(idx);
        int start = address - off;
        g_cache[idx].valid = 1;
        g_cache[idx].tag = tag;
        for (int i = 0; i < 16; i++) {
            g_cache[idx].data[i] = swap_int32(*((int32_t*)(dataMem + start + i * 4)));
        }
        return 0;
    }
}




