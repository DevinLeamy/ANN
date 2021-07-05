#include "./tests.h"
#include "./matrix.h"
#include <stdio.h>

#define LEN(arr) sizeof arr / sizeof arr[0]

static int test_dot_1()
{
  double **a_vals = init_2d(2, 1);
  a_vals[0][0] = 0.5;
  a_vals[1][0] = 0.3;
  struct Matrix *a = new_matrix(2, 1, a_vals);

  double **b_vals = init_2d(2, 2);
  b_vals[0][0] = 0.3; b_vals[0][1] = 0.5;
  b_vals[1][0] = 0.1; b_vals[1][1] = 0.2;
  struct Matrix *b = new_matrix(2, 2, b_vals);

  struct Matrix *c = b->dot(b, a);
  double des[2][1] = { {0.3}, {0.11} };

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 1; j++) {
      if (des[i][j] != (c->vals)[i][j])
        return 0;
    }
  }
  return 1;
}

int test_matrix() 
{
  FPI tests[] = { test_dot_1 };
  for (int i = 0; i < LEN(tests); i++)
    if (!tests[i]()) {
      printf("Error: Failed matrix test %d\n", i + 1);
      return 0;
    }
  return 1;
}