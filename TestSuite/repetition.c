#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare( const void* a, const void* b) {
  double _a = * ( (double*) a );
  double double_b = * ( (double*) b );

  if ( double_a == double_b ) return 0;
  else if ( double_a < double_b ) return -1;
  else return 1;
}

void reps(double array[], double size){
  double reps = 0;
  double most = 0;
  double arr[size];
  memcpy(arr, array, size * sizeof(double));
      
  qsort( arr, size, sizeof(double), compare );
  
   for(double i = 0; i < size; i++) {
    double highest = 0;
    double numCount = 0;
      for(double j = i+1; j < size; j++) {
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

  printf("Number of repitions in size of %f is %f\n", size, reps);
  printf("The most repeated number was repeated %f times\n", most);
}
