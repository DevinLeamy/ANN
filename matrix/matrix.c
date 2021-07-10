#include "./matrix.h"
#include "../math/math.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// init 2d array
double **init_2d(int rows, int cols, int rand) 
{
  double **arr = (double **) malloc(sizeof(double *) * rows);
  for (int i = 0; i < rows; i++) {
    arr[i] = (double *) malloc(sizeof(double) * cols);
    for (int j = 0; j < cols; j++)
      arr[i][j] = (rand == RANDOM_INIT)? random_dbl() : 0.0;
  }
  return arr;
}

// init vector
double *init_arr(int len, int rand)
{
  double *arr = (double *) malloc(sizeof(double) * len);
  for (int i = 0; i < len; i++)
    arr[i] = (rand == RANDOM_INIT)? random_dbl() : 0.0;
  return arr;
}

// duplicate a 2d array
static double **_dup_2d(int rows, int cols, double **vals)
{
  double **dup_vals = init_2d(rows, cols, RANDOM_INIT); 
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) 
      dup_vals[i][j] = vals[i][j]; 
  return dup_vals;
}

// free 2d array
static void _free_2d(int rows, double **vals) 
{
  for (int i = 0; i < rows; i++) 
    free(vals[i]);
  free(vals);
}

// free matrix
static void _free_matrix(struct Matrix *self) 
{
  _free_2d(self->rows, self->vals);
  free(self);
}

// dot product
static struct Matrix *_dot_product(struct Matrix *self, struct Matrix *x) 
{
  assert(self->cols == x->rows);

  // result dimensions
  int res_r = self->rows;
  int res_c = x->cols;

  struct Matrix *res = new_matrix(res_r, res_c, NULL);

  for (int i = 0; i < self->rows; i++) {
    for (int j = 0; j < x->cols; j++) {
      double sum = 0.0;
      for (int k = 0; k < self->cols; k++)
        sum += self->vals[i][k] * x->vals[k][j];
      (res->vals)[i][j] = sum;
    }
  }
  return res;
}

// apply activation func to values
static void _apply(struct Matrix *self, Activation f)
{
  for (int i = 0; i < self->rows; i++) {
    for (int j = 0; j < self->cols; j++) 
      (self->vals)[i][j] = f((self->vals[i][j]));
  }
}

// add matrices
static struct Matrix *_add_matrices(struct Matrix *self, struct Matrix *x) 
{
  // dimensions must match
  assert(self->rows == x->rows && self->cols == x->cols);

  struct Matrix *res = new_matrix(self->rows, self->cols, NULL);

  for (int i = 0; i < self->rows; i++) {
    for (int j = 0; j < self->cols; j++) 
      (res->vals)[i][j] = (self->vals)[i][j] + (x->vals)[i][j];
  }
  return res;
}

// constructor
// vals == NULL => fill with random  
struct Matrix *new_matrix(int rows, int cols, double **vals)
{
  struct Matrix *matrix = (struct Matrix *) malloc(sizeof(struct Matrix));
  matrix->rows = rows;
  matrix->cols = cols;
  matrix->vals = (vals == NULL)? init_2d(rows, cols, RANDOM_INIT) : _dup_2d(rows, cols, vals);
  matrix->free = _free_matrix;
  matrix->dot = _dot_product; 
  matrix->add = _add_matrices; 
  matrix->apply = _apply;

  return matrix;
}

// display
void display_matrix(struct Matrix *matrix)
{
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->cols; j++)
      printf("%5.3f ", (matrix->vals)[i][j]);
    printf("\n");
  }
}

