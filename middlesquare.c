#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int seed = 0;
int seedlen = 0;


int generatevalue(){
	//generates the next value in the random sequence and
	//returns it - this value is also set as the seed
	char squarestring[1048];
	char temp[1048];
	char middle[1048];
	int square = seed * seed;

        printf("Seed is %i\nSquare was %i\n", seed, square);

        sprintf(squarestring, "%i", square);
        printf("squarestring is %s\n", squarestring);
        while( strlen(squarestring) < (seedlen * 2)){
            strcpy(temp, squarestring);
            sprintf(squarestring, "0%s", temp);
        }
        printf("Squarestring is %s\n", squarestring);

	int returnval = 0;

        strncpy(middle, squarestring + (seedlen / 2), seedlen);
	returnval = atoi(middle);
	seed = returnval;
        return returnval;

}


int main(int argc, char* argv[]){
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


        seed = atoi(argv[1]);
        seedlen = strlen(argv[1]);
        int iterations = atoi(argv[2]);
	int* results = malloc(sizeof(int) * iterations);
        for(int i = 0; i < iterations; i++){
            results[i] = generatevalue();
	    printf("Value is %i\n", results[i]);
	}

	printf("Final results: [ ");
	for(int i = 0; i < iterations; i++){

		printf("%i ", results[i]);

	}
	printf("]\n");
	free(results);
}
