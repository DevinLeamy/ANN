#include "matrix.h"
#include "../math/math.h"
#include "../vector/vector.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void display_smatrix(SMatrix smatrix) {
  for (int i = 0; i < smatrix->rows; i++)
    display_vector(smatrix->cols, smatrix->vals[i]);
}

Matrix new_matrix(int rows, int cols, enum FillType fill_type) {
  Matrix matrix = (Matrix) malloc(sizeof(Vector) * rows);

  for (int i = 0; i < rows; i++)
    matrix[i] = new_vector(cols, fill_type);
  return matrix;
}

void free_matrix(Matrix matrix, int rows) {
  for (int i = 0; i < rows; i++) 
    free(matrix[i]);
  free(matrix);
}

SMatrix new_smatrix(int rows, int cols, enum FillType fill_value) {
  SMatrix smatrix = (SMatrix) malloc(sizeof(struct _SMatrix));
  smatrix->vals = new_matrix(rows, cols, fill_value);
  smatrix->rows = rows;
  smatrix->cols = cols;

  return smatrix;
}

void free_smatrix(SMatrix smatrix) {
  if (smatrix == NULL) return;

  free_matrix(smatrix->vals, smatrix->rows);
  free(smatrix);
}

