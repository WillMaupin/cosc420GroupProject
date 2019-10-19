/* PROJECT EULER PROBLEM 389
An unbiased single 4-sided die is thrown and its value, T, is noted.
T unbiased 6-sided dice are thrown and their scores are added together.
  The sum, C, is noted.
C unbiased 8-sided dice are thrown and their scores are added together.
 The sum, O, is noted.
O unbiased 12-sided dice are thrown and their scores are added together.
 The sum, D, is noted.
D unbiased 20-sided dice are thrown and their scores are added together.
 The sum, I, is noted.
Find the variance of I, and give your answer rounded to 4 decimal places.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include "dice.h"


int main(int argc, char** argv){
  MPI_Init(NULL, NULL);
  int rank, nprocs;
  MPI_Comm world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &nprocs);
  MPI_Comm_rank(world, &rank);


  if(argc < 2){
    if (rank == 0) printf("Useage: ./[Executable] [Iterations Per Process]\n\n");
    return 1;
  }

  srand(time(0) + rank);
  int iterations = atoi(argv[1]);
  //each processors local array of I values
  int *local_I = malloc(sizeof(int) * iterations);
  //array of all I values from all processes
  if(rank == 0) int *root_I = malloc(sizeof(int) * iterations * nprocs);// 'collection array'
  //array of each I values squared difference (I value - mean)
  double *sqrd_diff = malloc(sizeof(double) * iterations * nprocs); //'collection array'
  int i,j,k;

  //each processor calls rollDice and stores the result locally
  for(i=0; i<iterations; i++){
    local_I[i] = rollDice();
  }


  if(rank != 0){
    //processors other than the root sends its array of I values to the root process
    //to be used to calculate the variance of all I values
    MPI_Send(local_I, iterations, MPI_INT, 0, 0, world);
    free(local_I);  // done with processors local arrays
  }else{
    printf("nprocs: %d\n\n", nprocs); //mostly used for debugging, prints the number of processes being utilized
    for(i = 0; i<nprocs; i++){
      int *temp = malloc(sizeof(int) * iterations); //temporarily store arrays from other proc.
      //do not need to send/receive roots array of I values
      if(i!=0)  MPI_Recv(temp, iterations, MPI_INT, i, 0, world, MPI_STATUS_IGNORE);

      for(j = 0; j<iterations; j++){
        //do not need to send/receive root procs array, just read through and move
        //  to other arrays
        if(i == 0){
          root_I[j] = local_I[j];
          sqrd_diff[j] = local_I[j];
        }else{
          //read received arrays into 'collection' arrays
          root_I[iterations * i + j] = temp[j];
          sqrd_diff[iterations * i + j] = temp[j];
        }
      }
      free(temp);
    }


    double mean = 0;
    double variance = 0.0;

    if(rank==0){
      //find mean of all I values
      for(i = 0; i<iterations*nprocs; i++){
        mean += root_I[i];
      }
      //divide sum of all I values by the total number of times run
      mean /= (iterations * nprocs) - 1;

      for(i = 0; i<iterations*nprocs; i++){
        sqrd_diff[i] -= mean;         //I value minus mean
        sqrd_diff[i] *= sqrd_diff[i]; //squaring result from above
        variance += sqrd_diff[i];     //adding to sum of all variances
      }

      variance /= (nprocs*iterations)-1;              //average of all variances
      double ev = 2406376.3623;                        //actual solution
      printf("calculated v: %.4f\n", variance);       //calculated solution;
                                                      // variance of all I values
      printf("===============================\n");
      printf("expected   v: %11.4f\n", ev);
      printf("difference:   %.4f\n", ev - variance);  //prints how far off from
                                                      //the solution this attempt was
      printf("===============================\n");
    }
  }


  MPI_Finalize();
  free(root_I);
  free(sqrd_diff);
  return 0;
}
