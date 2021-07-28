#ifndef MATRIX_H
#define MATRIX_H

#include "../math/math.h"
#include "../vector/vector.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef double** Matrix;
typedef double* Vector;

struct SMatrix {
  int rows, cols;
  Matrix vals;
};

typedef struct SMatrix *SMatrix;

SMatrix new_smatrix(int, int, enum FillType);
Matrix new_matrix(int, int, enum FillType);

void display_smatrix(SMatrix);

void free_matrix(Matrix, int);
void free_smatrix(SMatrix);
#endif