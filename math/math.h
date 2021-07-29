#ifndef MATH_H
#define MATH_H

#define MODIFY_TRUE 1
#define MODIFY_FALSE 0

#define DERIVATIVE_TRUE 1
#define DERIVATIVE_FALSE 0 

#define TRUE 1
#define FALSE 0

#include "../matrix/matrix.h"
#include "../vector/vector.h"
#include <assert.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

// util
double random_double();
double add(double, double);
double sub(double, double);
double multiply(double, double);
void math_init();

// activations
double softmax(SVector, int, int);
SVector softmax_vector(SVector, int);
double sigmoid(double, int);
SVector sigmoid_vector(SVector, int);

// f(x, y) 
SMatrix component_wise_apply_matrix(SMatrix, SMatrix, double (*func)(double, double), int);
SVector component_wise_apply_vector(SVector, SVector, double (*func)(double, double), int);

SMatrix add_matrices(SMatrix, SMatrix, int);
SMatrix sub_matrices(SMatrix, SMatrix, int);

SVector add_vectors(SVector, SVector, int);
SVector sub_vectors(SVector, SVector, int);
SVector multiply_vectors(SVector, SVector, int);

SVector dot_matrix_vector(SMatrix, SVector);
SMatrix outer_product(SVector, SVector);

// f(x)
SMatrix apply_matrix(SMatrix, double (*func)(double), int);
SVector apply_vector(SVector, double (*func)(double), int);

double sum_vector(SVector);
double sum_matrix(SMatrix);

SMatrix transpose_matrix(SMatrix);
SVector scale_vector(SVector, double, int);

#endif
