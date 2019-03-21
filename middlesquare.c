/**
 * Serial Version of Middle Square Method
 *
 * --History--
 *
 * --How it Works--
 *  The Middle Square Method generates pseudorandom numbers through the
 *  following steps:
 *
 *  1) Take any number with 'n' digits, n being an even number
 *  2) Square this number
 *  3) If the square of the number is less than 2n, add leading zeros until
 *  	the result has 2n digits
 *  4) Take the middle n digits of the square- this is the next number in 
 *  	this sequence of pseudorandom numbers, and the next seed
 *
 * --Weaknesses of this Method--
 *  In its basic form, this method has never been practical enough for 
 *  real world use, for multiple reasons. Especially problematic is the 
 *  relatively small period of numbers that can be generated before
 *  this method begins repeating a small loop of the same values. As a general
 *  rule, for an 'n' digit seed, it is provable that the period can never be
 *  longer than 8^n values. 
 *
 *  Importantly, there is a version of this algorithm that solves these defects
 *  using  something called a Weyl sequence, which is designed to prevent
 *  reducing to zero and repetition. 
 *
 * --The Weyl Sequence--
 *  A Weyl sequence is generated based off of an integer 'k', which is 
 *  relatively prime to an integer modulus 'm'. 
 *  The sequence is all multiples of this integer (i.e. 0, k, 2k...).
 *  This sequence is equidistributed modulo m from the interval [0, m).
 *
 *  In practical application for this problem, the values in this sequence
 *  are added to the results of squaring before taking the middle values.
 *
 *
 *
 * Ian Staton
 *
 * Parallel PRNG algorithms
 *
 * TODO Add timing functionality
 * TODO Make main method return an array
 * TODO Convert this to use longs?
 * TODO Add Weyl sequence
 * TODO Change string implementation to bit shifting
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint32_t seed = 0;     //public seed value
int seedlen = 0;  //public length of the seed

//comment out this to prevent debug output
#define DEBUG

/**
 *  Generate the next value in the random sequence and returns it.
 *  This returned value is also set as the seed.
 */
int generatevalue(){
	char squarestring[1048];
	char temp[1048];
	char middle[1048];
	uint64_t square = seed * seed;
        #ifdef DEBUG
        printf("Seed is %u\nSquare is %lu\n", seed, square);
        #endif

        sprintf(squarestring, "%lu", square);
        #ifdef DEBUG
	printf("Squarestring is %s\n", squarestring);
        #endif

	while( strlen(squarestring) < (seedlen * 2)){
            strcpy(temp, squarestring);
            sprintf(squarestring, "0%s", temp);
        }
        #ifdef DEBUG
        printf("Squarestring is %s\n", squarestring);
        #endif
	

        strncpy(middle, squarestring + (seedlen / 2), seedlen);
	uint32_t returnval = atoi(middle);
	seed = returnval;
        return returnval;

}

int main(int argc, char* argv[]){

	//Argument error checking
	if(argc != 3)
	{
		printf("USAGE: middlesquare seed(int) iterations(int)");
		exit(EXIT_FAILURE);
	}

	//Ensure the length of the seed is even
	if( (strlen(argv[1]) % 2) != 0){
		printf("ERROR: Length of seed must be even.\n");
		exit(EXIT_FAILURE);
	}

	//Parse the command line
        seed = atoi(argv[1]);
        seedlen = strlen(argv[1]);
        int iterations = atoi(argv[2]);

	//Create a results array of a size equal to how many iterations
	// have been requested
	uint32_t* results = malloc(sizeof(uint32_t) * iterations);

	//Generate values and print as we go
        for(int i = 0; i < iterations; i++){
            results[i] = generatevalue();
            #ifdef DEBUG
	    printf("Value is %u\n", results[i]);
	    #endif
	}

	//Report final answer as a string 
	printf("Final results: [ ");
	for(int i = 0; i < iterations; i++){

		printf("%i ", results[i]);

	}
        printf("]\n");

	//Cleanup and exit
	free(results);
}
