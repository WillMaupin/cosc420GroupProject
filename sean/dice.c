#ifndef DICE_H
#define DICE_H

#include <time.h>

int rollTheDice(){
  srand(time(0));
  int dice_sizes = [4,6,8,12,20];
  int d4,d6,d8,d12,d20;

  int i,j, small_sum, total_sum;
  j = rand() % dice_sizes[0] + 1;
  printf("j: %d\n", j);
  for(i=0;i<4;i++){
    

  }

}


#endif
