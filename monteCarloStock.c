#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <tgmath.h>
#include <stdbool.h>

// Cumulative Normal Distribution Function
double normalCDF(double value)
{
   return 0.5 * erfc(-value * sqrt(.5));
}

/**
  * Monte Carlo Stock Market Simulation
  *
  *
  */
int main(int argc, char* argv[]) {
    double startVal = 10;
    double drift = .03;
    double standDev = .05;
    bool fry = false;
    bool mid = false;
    bool lcg = false;

    if(argc < 2 || argc > 4) {
        printf("USAGE: ./monteCarloStock randomGenMethod(int 1=lcg, 2=middlesquare, 3=threefry) *repeatx2*\n");
        exit(EXIT_FAILURE);
    }

    for(int i=1; i<argc; i++) {
        switch(atoi(argv[i])) {
            case 1: lcg = true; break;
            case 2: mid = true; break;
            case 3: fry = true; break;
            default: break;
        }
    }
    
    if(lcg) {
        FILE* input = fopen("out_lcg.txt", "r");
        FILE* output = fopen("stock_lcg.txt", "w");

        int nextRand = 0;

        double currVals[1000];
        double allVals[1000][100];

        for(int j=0; j<1000; j++) {
            fscanf(input, "%d", &nextRand);
            currVals[j] = startVal * exp(drift + (standDev * normalCDF(nextRand)));
            allVals[j][0] = currVals[j];
        }

        for(int i=1; i<100; i++) {
            for(int j=0; j<1000; j++) {
                fscanf(input, "%d", &nextRand);
                currVals[j] = currVals[j] * exp(drift + standDev * normalCDF(nextRand));
                allVals[j][i] = currVals[j];
            }
        }

        for(int i=0; i<1000; i++) {
            fprintf(output, "100 days for set %3d: ", i);
            for(int j=0; j<100; j++) {
                fprintf(output, "%.2f, ", allVals[i][j]);
            }
            fprintf(output, "\n");
        }

        fclose(input);
        fclose(output);
    }

    if(mid) {
        FILE* input = fopen("out_mid_par.txt", "r");
        FILE* output = fopen("stock_mid.txt", "w");

        fclose(input);
        fclose(output);
    }

    if(fry) {
        FILE* input = fopen("out_fry_par.txt", "r");
        FILE* output = fopen("stock_fry.txt", "w");

        fclose(input);
        fclose(output);
    }
    
}
