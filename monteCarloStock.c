#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "threefry.h"

# include <sys/time.h>
  struct timeval _tv;
#define START_TIMER(X) gettimeofday(&_tv, NULL); \
    double _timer_ ## X = _tv.tv_sec+(_tv.tv_usec/1000000.0);
#define STOP_TIMER(X) gettimeofday(&_tv, NULL); \
    _timer_ ## X = _tv.tv_sec+(_tv.tv_usec/1000000.0) - (_timer_ ## X);
#define GET_TIMER(X) (_timer_ ## X)

// Cumulative Normal Distribution Function
double normalCDF(double value)
{
   return 0.5 * erfc(-value * M_SQRT1_2);
}

/**
  * Monte Carlo Stock Market Simulation
  *
  *
  */
int main(int argc, char* argv[]) {
    double startVal = 10;
    double drift = .5;
    double standDev = 3;
    double rand;
    bool fry = false;
    bool mid = false;
    bool lcg = false;

    if(argc < 2 || argc > 4) {
        printf("USAGE: ./monteCarloStock randomGenMethod(int 1=lcg, 2=middlesquare, 3=threefry) *repeatx2*\n");
        exit(EXIT_FAILURE);
    }

    for(int i=1; i<argc; i++) {
        switch(argv[i]) {
            case 1: lcg = true; break;
            case 2: mid = true; break;
            case 3: fry = true; break;
            default: break;
        }
    }
    
    if(lcg) {
        
    }

    if(mid) {
        
    }

    if(fry) {
        
    }
    
}
