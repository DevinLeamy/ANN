#ifndef MATRIX_H
#define MATRIX_H

#include "../math/math.h"

#define RANDOM_INIT 1

struct Matrix {
  int rows, cols;
  double **vals;
  struct Matrix *(*dot)(struct Matrix *self, struct Matrix *x);
  struct Matrix *(*add)(struct Matrix *self, struct Matrix *x);
  void (*free)(struct Matrix *self); 
  void (*apply)(struct Matrix *self, Activation f);
};

struct Matrix *new_matrix(int rows, int cols, double **vals);
// make display a 'method'
void display_matrix(struct Matrix *matrix);
double **init_2d(int rows, int cols, int rand);
double *init_arr(int len, int rand);

#endif