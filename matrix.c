#include "./matrix.h"
#include <stdlib.h>
#include <stdio.h>

// init 2d array - fill with zeros
double **init_2d(int rows, int cols) 
{
  double **arr = (double **) malloc(sizeof(double *) * rows);
  for (int i = 0; i < rows; i++) {
    arr[i] = (double *) malloc(sizeof(double) * cols);
    for (int j = 0; j < cols; j++) 
      arr[i][j] = 0.0;
  }
  return arr;
}

// duplicate a 2d array
static double **_dup_2d(int rows, int cols, double **vals)
{
  double **dup_vals = init_2d(rows, cols); 
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
static struct Matrix *_dot_product(struct Matrix *self, struct Matrix *y) 
{
  if (self->cols != y->rows) {
    printf("Error: Matrices are not compatible for dot product");
    exit(1);
  }
  // result values
  int res_r = self->rows, res_c = y->cols;
  double **res = init_2d(res_r, res_c);

  for (int i = 0; i < self->rows; i++) {
    for (int j = 0; j < y->cols; j++) {
      double sum = 0.0;
      for (int k = 0; k < self->cols; k++)
        sum += self->vals[i][k] * y->vals[k][j];
      res[i][j] = sum;
    }
  }
  struct Matrix *result_mat = new_matrix(res_r, res_c, res);
  _free_2d(res_r, res); // res was duplicated in new_matrix(...)
  return result_mat;
}

// constructor
struct Matrix *new_matrix(int rows, int cols, double **vals)
{
  struct Matrix *matrix = (struct Matrix *) malloc(sizeof(struct Matrix));
  matrix->rows = rows;
  matrix->cols = cols;
  matrix->vals = _dup_2d(rows, cols, vals);
  matrix->free = _free_matrix;
  matrix->dot = _dot_product; 
  
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

