#include <stdlib.h>
#include <stdint.h>

#include <vector>


#define BITMASK(n) ((1 << n) - 1)

int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int logOf2(int num) {
    int result = 0;
    while (num > 1) {
        result++;
        num /= 2;
    }
    return result;
}

class Block {
    public:

    std::vector<int> data;
    int last_reference_timestamp;
    char valid;
    int tag;

    Block(int block_size) : data(block_size, 0),
        last_reference_timestamp(0),
        valid(0) {
    }
};

class Set {
    // set of block
    
    public:

    // num of blocks in set.
    // if direct-map,            set_size == 1
    // if N - way associativity, set_size == N
    int set_size;

    std::vector<Block> blocks;

    Set(int associativity, int block_size) :
        set_size = associativity,
        blocks(associativity, Block(block_size)) {
    }
};

class Cache {

    // 32_bit memory address
    // block_size : variable

    // type 1 :
    //      total 1024 bytes
    //      direct_mapped
    //      write-through, no write allocate
    //      
    // type 2 :
    //      total 4096 bytes
    //      2 - way set associative
    //      LRU replacement
    //      write back, write allocate

    public :
     
    std::vector<Set> sets;

    int loadWord(uint32_t address) {
        reference_count++;
        decodeAddress(address);
        for (int i = 0; i < associativity; i++) {
            if (
                sets.at(idx_field).blocks.at(i).valid == 1 &&
                sets.at(idx_field).blocks.at(i).tag == tag_field
            ) { // cache hit
                
                // increment cache hit counter
                cache_hit_count++;
                
                // set last used time stamp of block referenced
                sets.at(idx_field).blocks.at(i).last_reference_timestamp = reference_count;
                
                // return word
                return sets.at(idx_field).blocks.at(i).data.at(off_field);
            }
        }
        
        // cache miss
        int block_start_address = address - off_field;
    }

    void storeWord(uint32_t address, int word) {
        reference_count++;
        decodeAddress(address);

    }


    void decodeAddress(uint32_t address) {
        tag_field = address >> (offst_field_size + index_field_size);
        idx_field = (address >> offst_field_size) & BITMASK(index_field_size);
        off_field = address & BITMASK(offst_field_size);
    }

    int reference_count;
    int cache_hit_count;

    int associativity;
    int num_of_set;
    int block_size;

    int offst_field_size;
    int index_field_size;

    int tag_field;
    int idx_field;
    int off_field;

    Cache(int associativity, int block_size, int num_of_set) :
        associativity(associativity),
        block_size(block_size),
        num_of_set(num_of_set),
        reference_count(0),
        cache_hit_count(0),
        sets(num_of_set, Set(associativity, block_size)) {    
            offst_field_size = logOf2(block_size);
            index_field_size = logOf2(num_of_set);
    }

};
