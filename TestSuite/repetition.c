#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare( const void* a, const void* b) {
  double double_a = * ( (double*) a );
  double double_b = * ( (double*) b );

  if ( double_a == double_b ) return 0;
  else if ( double_a < double_b ) return -1;
  else return 1;
}

void reps(double array[], double size){
  printf("Before declarations\n");
  double reps = 0;
  double most = 0;
  double arr[(int) size];
  memcpy(arr, array, size * sizeof(double));
  printf("After memcpy\n");
  qsort( arr, size, sizeof(double), compare );
  printf("After qsort\n");
   for(int i = 0; i < size; i++) {
    double highest = 0;
    double numCount = 0;
      for(int j = i+1; j < size; j++) {
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
