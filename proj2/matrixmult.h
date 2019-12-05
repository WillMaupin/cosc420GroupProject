#ifndef MATRIXMULT_H
#define MATRIXMULT_H

typedef struct matrix{
  int rows, cols;
  int* arr;
} matrix;

void matrixMult(matrix*,matrix*,matrix*);

#endif
