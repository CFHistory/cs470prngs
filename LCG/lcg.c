#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif
/**
 * LCG - Linear Congruential Generator
 *
 * Parallel evaluation - From viewing the LCG code, there seems to be a carried dependancy 
 * in the continued creation of the seed. The value of the seed relies on the previous value
 * of the seed and values are created in a loop. As such there is a loop based dependancy 
 * that does not allow for parallelization of the PRNG. 
 *
 * Alternate evaluation - As the LCG can not be parallelized, an alternate question can be
 * asked of whether or not the generation of numbers can be sped up if processes create a
 * portion of the workload. Another issue that could be addressed is whether or not a bad
 * seed can be fixed with parallelization and distribution of data. The reason for addressing
 * this is if seeds are generated at random and values need to be within a certain range. For
 * example in this problem -2^31 up to 2^31.
 * 
 * Say a, b, and c, are all terrible seeds. With all the values being low, and given the range
 * of 2^32, with the LCG method there would be no way to reach higher values. With the 
 * introduction of multiplaction to these values based of rank and modulus you are able to reach
 * the higher numbers increasing width of values while also maintaining lower values given by
 * the original seed. This will not fix the original seed, but will allow for other processes
 * to increase the width of values for monte carlo problems i.e. getting better estimates.
 *
 * Example run: OMP_NUM_THREADS=n ./lcg a b c
 *
 * n = number of threads, a,b,c = long int value
 *
 * Future testing needed: 
 *
 * Montecarlo output comparisons (R charts)
 * Timing comparisons alongside (serial value gen vs. parallel value gen)
 * 
 * Created By: Michael Mederos 
 *
 * */

long lcg(long a, long b, long c, long seed) {
    return (b * seed + c) % a;
}

long power(int base, int mult) {
    long ret = (long) base;
    for (int i = 0; i < mult; i++){
	ret *= base;
    }
    return ret;
}
 
int main(int argc, char **argv) {
    
    if( argc == 4 ) {

        #ifdef _OPENMP
        #pragma omp parallel
        #endif
        {
            unsigned long a,b,c,seed;
            a =(unsigned long) atoi(argv[1]);
            b =(unsigned long) atoi(argv[2]);
            c =(unsigned long) atoi(argv[3]);
            int myRank = 0;            
            
            #ifdef _OPENMP            
            myRank =  omp_get_thread_num();
            #endif
	    printf("My rank is %d\n", myRank);
            srand(time(0) + myRank + 1);
            seed = (unsigned long) rand();

            a = (a * (power(100,myRank))) % power(2,32);
            b = (b * (power(100,myRank))) % power(2,32);
            c = (c * (power(100,myRank))) % power(2,32);
	    printf("seed is %lu\n",seed);
            seed = (seed * (power(100,myRank))) % power(2,32);

            for (int i = 0; i < 10; i++) {
                seed = lcg(a,b,c,seed);
                #ifdef _OPENMP
                #pragma omp critical
                #endif
                printf("%d : with numbers %ld\n", myRank,  seed);
            }
        }
    }
    else if( argc > 4 ) {
        printf("Too many arguments supplied. 3 Arguments expected\n");
    }
    else {
        printf("3 Arguments expected in form int, a b c \n");
    }
 
    return 0;
}
