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
  return rand() % 2 +1;
  // return rolls_to_make[4];
}


#endif
