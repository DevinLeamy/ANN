#include "./matrix.h"

int main()
{
  double **a_vals = init_2d(2, 1);
  a_vals[0][0] = 0.5;
  a_vals[1][0] = 0.3;
  struct Matrix *a = new_matrix(2, 1, a_vals);
  display_matrix(a);

  double **b_vals = init_2d(2, 2);
  b_vals[0][0] = 0.3;
  b_vals[0][1] = 0.5;
  b_vals[1][0] = 0.1;
  b_vals[1][1] = 0.2;
  struct Matrix *b = new_matrix(2, 2, b_vals);

  display_matrix(b);

  struct Matrix *c = b->dot(b, a);

  display_matrix(c);
  return 0;
}