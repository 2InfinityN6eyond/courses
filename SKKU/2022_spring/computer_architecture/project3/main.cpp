#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <memory.h>
#include <math.h>

#include "mips_sim.hpp"
//#pragma warning(disable: 4996)



int cache_reference_counter;
int cache_hit_counter;
int8_t cache_type;
cache Cache[640];

int32_t* instruction_memory;
int8_t* data_memory;

int32_t PC;
int32_t reg[NUM_REGISTERS];
instruction* inst;
int inst_count;
int last_referenced_timestamp[160][2];


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
        printf("usage : ./mips_sim cache_type block_size num_of_inst inst_file_path data_file_path");
        exit(1);
    }

    cache_type = 1;
    if (!strcmp(argv[1], "2"))
        cache_type = 2;

    for (i = 0; i < 64; i++)
        Cache[i].valid = 0;

    int block_size = atoi(argv[2]);
    cache1_off_bit_num = logOf2(block_size);
    cache1_idx_bit_num = logOf2(1024 / block_size);
    cache2_off_bit_num = logOf2(block_size);
    cache2_idx_bit_num = logOf2(2048 / block_size);

    instruction_memory = (int32_t*)malloc(MAXBUF);
    if (NULL == instruction_memory) {
        printf("instruction memory assign failed\n");
        exit(1);
    }
    memset(instruction_memory, 0xFF, MAXBUF);
    readFile(argv[4], instruction_memory, 4);

    data_memory = (int8_t*)malloc(MAXBUF);
    if (NULL == data_memory) {
        printf("data memory assign failed\n");
        exit(1);
    }
    memset(data_memory, 0xFF, MAXBUF);
    if (6 == argc) {
        readFile(argv[5], data_memory, 1);
    }

    PC = 0;
    for (i = 0; i < NUM_REGISTERS; i++)
        reg[i] = 0;

    inst = (instruction *)malloc(sizeof(instruction));
    if (NULL == inst) {
        printf("instruction assign failed\n");
        exit(1);
    }

    int32_t N = atoi(argv[3]);
    for (i = 0; i < N; i++)
    {
        inst_count++;
        decodeInstruction(reverseInt32(*(instruction_memory + PC++)));
        if (isValidInstruction())
            execute();
        else
            break;
    }

    printf("Instructions: %d\n", inst_count);
    printf("Total: %d\n", cache_reference_counter);
    printf("Hits: %d\n", cache_hit_counter);
    printf("Misses: %d\n", cache_reference_counter - cache_hit_counter);

    free(inst);
    free(instruction_memory);
    if (NULL != data_memory) free(data_memory);
	return 0;
}
