#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "threefry.h"

#ifdef _OPENMP
# include <omp.h>
# define START_TIMER(X) double _timer_ ## X = omp_get_wtime();
# define STOP_TIMER(X) _timer_ ## X = omp_get_wtime() - (_timer_ ## X);
# define GET_TIMER(X) (_timer_ ## X)
#else
# include <sys/time.h>
  struct timeval _tv;
#define START_TIMER(X) gettimeofday(&_tv, NULL); \
    double _timer_ ## X = _tv.tv_sec+(_tv.tv_usec/1000000.0);
#define STOP_TIMER(X) gettimeofday(&_tv, NULL); \
    _timer_ ## X = _tv.tv_sec+(_tv.tv_usec/1000000.0) - (_timer_ ## X);
#define GET_TIMER(X) (_timer_ ## X)
#endif

//Uncomment this line for raw output
//#define DEBUG

//Uncomment this for outputting to a file
#define CATOUT

/**
 *  Parallel version of the Threefry Method
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

    threefry2x64_ctr_t* results;

    if(argc < 3){
        /**
          *  Usage: ./threefry_ser unsigned long seed, unsigned long count
          */
        printf("USAGE: 3fry_ser seed(unsigned long) count(unsigned long)\n");
        exit(EXIT_FAILURE);
    } 

    seed = atol(argv[1]);
    count = atol(argv[2]);

    results = malloc(sizeof(threefry2x64_ctr_t) * count);

    START_TIMER(genvals);
    #ifdef _OPENMP
    #pragma omp parallel
    #endif
    {
        int start = ( (count / omp_get_max_threads() ) * omp_get_thread_num());
        #ifdef DEBUG
        printf("Value of start is %i\n", start);
        #endif
    	threefry2x64_key_t key = {{seed,0}};
    	threefry2x64_ctr_t ctr = {{start ,0}};

    	for(int i = 0; i < (count/omp_get_max_threads()); i++){
        	results[start + i] = threefry2x64(ctr, key);
        	ctr.v[0]++;
                
    	}
    }

    STOP_TIMER(genvals);

    #ifdef DEBUG
    FILE* output = fopen("out_fry_par.txt", "w");
    printf("Final Results: [");
    for(int j = 0; j < count; j++){
        printf(" %lu ",results[j]);
        fprintf(output, "%lu\n", results[j]); 
    }
    printf("]\n");
    fclose(output);
    #endif

    
    #ifdef CATOUT
    for(int k = 0; k < count; k++){
        printf("%lu\n", results[k]);
    }
    #else 
    printf("Time taken: %.6f\n", GET_TIMER(genvals));
    #endif

 
    free(results);

    return 0;

}
