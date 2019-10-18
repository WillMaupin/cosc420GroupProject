#include <stdio.h>
#include <stdlib.h>
#include "dice.h"

int main(int argc, char** argv){
  int *arr = malloc(sizeof(int)*9);
  double mean = 0 ;
  int n = 9;
  for(int i=0; i<n; i++){
    arr[i] = i+2;
    mean+= arr[i];
    printf("arr[%d]: %d\n", i, arr[i]);
  }
  mean /= n;

  printf("mean: %f\n",mean);
  double v = variance(arr, n, mean);

  printf("variance: %f\n", v);

  return 0;
}
