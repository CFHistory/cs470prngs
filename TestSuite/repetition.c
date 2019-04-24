/**
 * repetition.c
 *
 * Use: input an array of longs to determine the number of repitions given the size of input and the highest
 * number of reptitions in the array
 *
 * Author: Michael Mederos
 *
 * Params: arr[] - the array to be used for testing
 * 	   size - the size of the array being used
 */

#include <stdio.h>
#include <stdlib.h>

int compare( const void* a, const void* b) {
  long long_a = * ( (long*) a );
  long long_b = * ( (long*) b );

  if ( long_a == long_b ) return 0;
  else if ( long_a < long_b ) return -1;
  else return 1;
}

void reps(long arr[], long size){
  long reps = 0;
  long most = 0;
      
  qsort( arr, size, sizeof(long), compare );

   for(long i = 0; i < size; i++) {
    long highest = 0;
    long numCount = 0;
      for(long j = i+1; j < size; j++) {
        if(arr[i] == arr[j]) {
          numCount += 1;
          highest++;
        }
      }
    if (highest > most) {
      most = highest;
    }
    reps += numCount;
    i += numCount;
  }

  printf("Number of repitions in size of %ld is %ld\n", size, reps);
  printf("The most repeated number was repeated %ld times\n", most);
}
