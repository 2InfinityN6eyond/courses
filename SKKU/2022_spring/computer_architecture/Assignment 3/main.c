#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <memory.h>
#include <math.h>

#include "mips_simulator.h"
//#pragma warning(disable: 4996)



int g_total;
int g_hits;
int8_t g_cacheType;
cache g_cache[640];

int32_t* instMem;
int8_t* dataMem;

int32_t PC;
int32_t reg[RESISTERNUM];
instruction* inst;
int inst_count;
int LRU[160][2];


int cache1_off_bit_num;
int cache1_idx_bit_num;

int cache2_off_bit_num;
int cache2_idx_bit_num;

int logOf2(int num) {
    int result = 0;
    while (num > 1) {
        result++;
        num /= 2;
    }
    return result;
}

int main(int argc, char* argv[]) {

    int i;
    if ((5 != argc) && (6 != argc)) {
        printf("Arguments count must be 4 or 5, not %d\n", argc - 1);
        exit(1);
    }

    g_cacheType = 1;
    if (!strcmp(argv[1], "2"))
        g_cacheType = 2;

    for (i = 0; i < 64; i++)
        g_cache[i].valid = 0;

    int block_size = atoi(argv[2]);
    cache1_off_bit_num = logOf2(block_size);
    cache1_idx_bit_num = logOf2(1024 / block_size);
    cache2_off_bit_num = logOf2(block_size);
    cache2_idx_bit_num = logOf2(2048 / block_size);

    instMem = (int32_t*)malloc(MAXBUF);
    if (NULL == instMem) {
        printf("Can not malloc instruction memory\n");
        exit(1);
    }
    memset(instMem, 0xFF, MAXBUF);
    readFile(argv[4], instMem, 4);

    dataMem = (int8_t*)malloc(MAXBUF);
    if (NULL == dataMem) {
        printf("Can not malloc data memory\n");
        exit(1);
    }
    memset(dataMem, 0xFF, MAXBUF);
    if (6 == argc) {
        readFile(argv[5], dataMem, 1);
    }

    PC = 0;
    for (i = 0; i < RESISTERNUM; i++)
        reg[i] = 0;

    inst = (instruction *)malloc(sizeof(instruction));
    if (NULL == inst) {
        printf("Can not malloc inst\n");
        exit(1);
    }

    int32_t N = atoi(argv[3]);
    for (i = 0; i < N; i++)
    {
        inst_count++;
        instDecode(swap_int32(*(instMem + PC++)));
        if (isValidInstruction())
            execution();
        else
            break;
    }

    printf("Instructions: %d\n", inst_count);
    printf("Total: %d\n", g_total);
    printf("Hits: %d\n", g_hits);
    printf("Misses: %d\n", g_total - g_hits);

    free(inst);
    free(instMem);
    if (NULL != dataMem) free(dataMem);
	return 0;
}
