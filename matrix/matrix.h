#ifndef MATRIX_H
#define MATRIX_H

#include "../vector/vector.h"

typedef double** Matrix;

struct _SMatrix {
  int rows, cols;
  Matrix vals;
};

typedef struct _SMatrix* SMatrix;

SMatrix new_smatrix(int, int, enum FillType);
Matrix new_matrix(int, int, enum FillType);

void display_smatrix(SMatrix);

void free_matrix(Matrix, int);
void free_smatrix(SMatrix);
#endif