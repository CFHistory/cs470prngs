#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "threefry.h"

/**
 *  Serial version of the Threefry Method
 *
 *  How it works
 *
 *  Threefry works by iterating over its key and counter values over a series of rounds. 
 *   Every round, a mix function is executed over the data to produce the next value of the data. Every four rounds,
 *   the initial key is added to the current value. After the last round, a final addition of the key 
 *   is applied, and the full data is xored with the initial value. The result of this process is one 
 *   randomly generated number in a sequence. 
 *
 *  Threefry works well in parallel systems because it is partially based off of a linearly-incrementing counter. 
 *  By increasing this counter by a set amount, you can effectively and easily divide out the work of generating
 *  random numbers amongst many nodes, using a single seed.
 *  
 *  Weaknesses of this Method
 *
 *
 */
int main(int argc, char* argv[]) {
    long seed;
    long count;    

    if(argc < 3){
        /**
          *  Usage: ./threefry_ser unsigned long seed, unsigned long count
          */
        printf("USAGE: 3fry_ser seed(unsigned long) count(unsigned long)\n");
        exit(EXIT_FAILURE);
    } 

    seed = atol(argv[1]);
    count = atol(argv[2]);

    threefry2x64_key_t key = {{seed,0}};
    threefry2x64_ctr_t ctr = {{0,0}};

    for(int i = 0; i < count; i++){
        printf("Result: %lu\n", threefry2x64(ctr, key));
        ctr.v[0]++;
    }
    

}
