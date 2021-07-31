#include "math.h"

// normalize on (-1, 1)
static double _normalize(long min_x, long max_x, long x) {
  return (double) (x - min_x) / (max_x - min_x);
}

// range(-1, 1) 
double random_double() {
  long x = rand(); 
  return _normalize(0l, RAND_MAX, x);
}

double softmax(SVector v, int index, int derivative) {
  if (derivative)
    return softmax(v, index, FALSE) * (1 - softmax(v, index, FALSE));
  SVector v_exp = apply_vector(v, exp, MODIFY_FALSE);
  double v_exp_sum = sum_vector(v_exp);

  double softmax = v_exp->vals[index] / v_exp_sum;
  free_svector(v_exp);

  return softmax;
}

SVector softmax_vector(SVector v, int derivative) {
  SVector v_exp = apply_vector(v, exp, MODIFY_FALSE);
  double v_exp_sum = sum_vector(v_exp);
  if (derivative) {
    for (int i = 0; i < v->length; i++) {
      double softmax = v_exp->vals[i] / v_exp_sum;
      v_exp->vals[i] = softmax * (1 - softmax); 
    }
    return v_exp;
  }

  for (int i = 0; i < v_exp->length; i++)
    v_exp->vals[i] /= v_exp_sum;
  return v_exp;
}

double sigmoid(double x, int derivative) {
  if (derivative) 
    return sigmoid(x, FALSE) * (1 - sigmoid(x, FALSE));
  return 1.0 / (1.0 + exp(-1.0 * x));
}

SVector sigmoid_vector(SVector v, int derivative) {
  SVector res = new_svector(v->length, FILL_ZERO);

  for (int i = 0; i < v->length; i++)
    res->vals[i] = sigmoid(v->vals[i], derivative);
  return res;
}

double sum_vector(SVector v) {
  double sum = 0.0;
  for (int i = 0; i < v->length; i++)
    sum += v->vals[i];
  return sum;
}

double sum_matrix(SMatrix m) {
  double sum = 0.0;
  for (int i = 0; i < m->rows; i++) 
    for (int j = 0; j < m->cols; j++) 
      sum += m->vals[i][j];
  return sum;
}

SVector dot_matrix_vector(SMatrix m, SVector v) {
  assert(m->cols == v->length);

  SVector prod = new_svector(m->rows, FILL_RANDOM);
  for (int i = 0; i < m->rows; i++) {
    double sum = 0;
    for (int j = 0; j < v->length; j++) 
      sum += m->vals[i][j] * v->vals[j];
    prod->vals[i] = sum;
  }

  return prod;
}

double percentage(int a, int b) {
  return a / (double) b * 100;
}

double add(double a, double b) {
  return a + b;
}

double sub(double a, double b) {
  return a - b;
}

double multiply(double a, double b) {
  return a * b;
}

SMatrix component_wise_apply_matrix(SMatrix m1, SMatrix m2, double (*func)(double, double), int modify) {
  assert(m1->rows == m2->rows && m1->cols == m2->cols);
  SMatrix res = (modify)? m1 : new_smatrix(m1->rows, m1->cols, FILL_ZERO);

  for (int i = 0; i < m1->rows; i++) 
    for (int j = 0; j < m1->cols; j++)
      res->vals[i][j] = func(m1->vals[i][j], m2->vals[i][j]);
  return res;
}

SVector component_wise_apply_vector(SVector v1, SVector v2, double (*func)(double, double), int modify) {
  assert(v1->length == v2->length);
  SVector res = (modify)? v1 : new_svector(v1->length, FILL_ZERO);

  for (int i = 0; i < v1->length; i++)
    res->vals[i] = func(v1->vals[i], v2->vals[i]);
  return res;
}

SMatrix apply_matrix(SMatrix m, double (*func)(double), int modify) {
  SMatrix res = (modify)? m : new_smatrix(m->rows, m->cols, FILL_ZERO);

  for (int i = 0; i < m->rows; i++)
    for (int j = 0; j < m->cols; j++)
      res->vals[i][j] = func(res->vals[i][j]);
  return res;
}

SVector apply_vector(SVector v, double (*func)(double), int modify) {
  SVector res = (modify)? v : new_svector(v->length, FILL_ZERO);

  for (int i = 0; i < v->length; i++)
    res->vals[i] = func(v->vals[i]);
  return res;
}

SMatrix add_matrices(SMatrix m1, SMatrix m2, int modify) {
  return component_wise_apply_matrix(m1, m2, add, modify);
}

SMatrix sub_matrices(SMatrix m1, SMatrix m2, int modify) {
  return component_wise_apply_matrix(m1, m2, sub, modify);  
}

SVector add_vectors(SVector v1, SVector v2, int modify) {
  return component_wise_apply_vector(v1, v2, add, modify);
}

SVector sub_vectors(SVector v1, SVector v2, int modify) {
  return component_wise_apply_vector(v1, v2, sub, modify);
}

SVector multiply_vectors(SVector v1, SVector v2, int modify) {
  return component_wise_apply_vector(v1, v2, multiply, modify);
}

SVector scale_vector(SVector v, double factor, int modify) {
  SVector res = (modify)? v : new_svector(v->length, FILL_ZERO);

  for (int i = 0; i < v->length; i++)
    res->vals[i] = v->vals[i] * factor;
  return res;
}

SMatrix scale_matrix(SMatrix m, double factor, int modify) {
  SMatrix res = (modify)? m : new_smatrix(m->rows, m->cols, FILL_ZERO);
  
  for (int i = 0; i < m->rows; i++)
    for (int j = 0; j < m->cols; j++)
      res->vals[i][j] = m->vals[i][j] * factor;
  return res;
}

SMatrix outer_product(SVector v1, SVector v2) {
  SMatrix product = new_smatrix(v1->length, v2->length, FILL_ZERO);

  for (int i = 0; i < v1->length; i++)  
    for (int j = 0; j < v2->length; j++)
      product->vals[i][j] = v1->vals[i] * v2->vals[j];
  
  return product;
}

SMatrix transpose_matrix(SMatrix m) {
  SMatrix transposed = new_smatrix(m->cols, m->rows, FILL_ZERO);

  for (int i = 0; i < m->rows; i++) 
    for (int j = 0; j < m->cols; j++)
      transposed->vals[j][i] = m->vals[i][j];
  return transposed;
}

int argmax_vector(SVector v) {
  double max_val = v->vals[0]; 
  int max_idx = 0;

  for (int i = 0; i < v->length; i++)
    if (v->vals[i] > max_val) {
      max_val = v->vals[i];
      max_idx = i;
    }
  
  return max_idx;
}

void math_init() {
  srand(time(NULL));
}