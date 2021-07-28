#ifndef MATH_H
#define MATH_H

#define TRUE 1
#define FALSE 0

#include "matrix.h"
#include "assert.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

double sigmoid(double, int);
SVector sigmoid_vector(SVector, int);
double softmax(SVector, int, int);
SVector softmax_vector(SVector, int);

double random_double();
SMatrix add_matrices(SMatrix, SMatrix, int);
SMatrix sub_matrices(SMatrix, SMatrix, int);
void math_init();

#endif
