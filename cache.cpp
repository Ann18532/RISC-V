#include<bits/stdc++.h>
using namespace std;

int MEM[1024]={0};
int R[32]={0};

const int DEFAULT_CACHE_SIZE=64;  // Default cache size
const int BLOCK_SIZE=4;            // Block size (4 bytes)
const int BLOCK_COUNT=DEFAULT_CACHE_SIZE/BLOCK_SIZE; // Number of blocks in cache


struct CacheLine {
    int tag;
    int data[BLOCK_SIZE];  // Array to hold all data for the block
    bool valid;

    CacheLine() : tag(-1), valid(false) {
       fill_n(data, BLOCK_SIZE, 0);  // Initialize data to zero
    }
};


class Cache {
private:
    vector<CacheLine> cache;

public:
    Cache() {
        cache.resize(BLOCK_COUNT);
    }

    void getTagIndexOffset(int address, int &tag, int &index, int &offset) {
        int offsetBits = log2(BLOCK_SIZE);               // 2 bits for offset
        int indexBits = log2(BLOCK_COUNT);               // 4 bits for index

        // Calculate offset
        offset = address & (BLOCK_SIZE - 1);             // Last 2 bits for offset

        // Calculate index
        index = (address / BLOCK_SIZE) % BLOCK_COUNT;    // Index into cache

        // Calculate tag
        tag = address >> (offsetBits + indexBits);       // Higher bits for tag
    }

    int read(int address) {
        int tag, index, offset;
        getTagIndexOffset(address, tag, index, offset);

        if (cache[index].valid && cache[index].tag == tag) {
            return cache[index].data[offset]; // Return the specific byte in the block
        } else {
            // Load block from main memory into cache
            cache[index].tag = tag;
            for (int i = 0; i < BLOCK_SIZE; ++i) {
                cache[index].data[i] = MEM[(address / BLOCK_SIZE) * BLOCK_SIZE + i]; // Load entire block
            }
            cache[index].valid = true;
            return cache[index].data[offset]; // Return the specific byte in the block
        }
    }

    void write(int address, int data) {
        int tag, index, offset;
        getTagIndexOffset(address, tag, index, offset);

        // Load block if it's not valid
        if (!cache[index].valid || cache[index].tag != tag) {
            cache[index].tag = tag;
            for (int i = 0; i < BLOCK_SIZE; ++i) {
                cache[index].data[i] = MEM[(address / BLOCK_SIZE) * BLOCK_SIZE + i]; // Load entire block
            }
            cache[index].valid = true;
        }

        // Write data to the correct offset in the block
        cache[index].data[offset] = data;
        MEM[address] = data; // Also write back to main memory
    }
};