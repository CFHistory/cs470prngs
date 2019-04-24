#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare( const void* a, const void* b) {
  long long_a = * ( (long*) a );
  long long_b = * ( (long*) b );

  if ( long_a == long_b ) return 0;
  else if ( long_a < long_b ) return -1;
  else return 1;
}

void reps(long array[], long size){
  long reps = 0;
  long most = 0;
  long arr[size];
  memcpy(arr, array, size * sizeof(long));
      
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
