#ifndef DICE_H
#define DICE_H

#include <time.h>

int rollTheDice(){
  // srand();
  int dice_sizes[] = {4,6,8,12,20};
  int roll,             // result of rolling a die
      rolls_to_make[5], // number of dice to roll ('T','C',O','D','I' in problem discripton)
      i, j;             // indeces

  rolls_to_make[0] = rand() % dice_sizes[0] + 1;

  for(i=1; i<5; i++){
    rolls_to_make[i] = 0;
    for(j=0; j< rolls_to_make[i-1]; j++){
      roll = rand() % dice_sizes[i] + 1;
      rolls_to_make[i] += roll;
    }
  }

  // for(i=0;i<5;i++){
  //   printf("rtm[%d]: %d\n", i, rolls_to_make[i]);
  // }
  // puts
  // return 1;
  // return rand() % 2

  return rolls_to_make[4];
}

double variance(int* arr, int n, double mean){
  double* sqr_diff = malloc(sizeof(double)*n);

  printf("===========================\n");
  for(int i=0; i<n; i++){
    printf("arr[%d]: %d\n", i, arr[i]);
  }

  printf("===========================\n");
  for(int i=0; i<n; i++){
    sqr_diff[i] = arr[i] - mean;
    sqr_diff[i] *= sqr_diff[i];
    printf("sqr_diff[%d]: %f\n", i, sqr_diff[i]);
  }

  printf("===========================\n");
  double v = 0.0;
  for(int i=0; i<n; i++){
    v += sqr_diff[i];
  }

  v/=n;
  return v;
} //end variance()


/*variance:
  -find the mean (above)
  -for each number, subtract the mean and square the result
      (the squared difference)
  -find average of those squared differences
*/
// }


#endif
