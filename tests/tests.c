// #include "./tests.h"
// #include "../net/net.h"
// #include "../matrix/matrix.h"
// #include "../math/math.h"
// #include <stdio.h>
// #include <stdlib.h>

// double **a1, **b1, **c1;
// double a1_vals[2][1] = {
//   { 0.5 },
//   { 0.3 }
// };
// double b1_vals[2][2] = {
//   { 0.3, 0.5 },
//   { 0.1, 0.2 }
// };
// double c1_vals[2][1] = { 
//   { 0.3 }, 
//   { 0.11 } 
// };

// double **a2, **b2, **c2;
// double a2_vals[2][1] = {
//   { 1.0 },
//   { 2.0 }
// };
// double b2_vals[2][1] = {
//   { 3.0 },
//   { 4.0 }
// };
// double c2_vals[2][1] = {
//   { 4.0 },
//   { 6.0 }
// };

// int *a3;
// int a3_vals[] = {};
// int b3 = 5;
// int c3 = 5;
// double *d3;
// double d3_vals[] = { 0.3, 0.3, 0.3, 0.3, 0.3 };

// int *a4;
// int a4_vals[] = { 3, 4, 5 };
// int b4 = 5;
// int c4 = 5;
// double *d4;
// double d4_vals[] = { 0.3, 0.3, 0.3, 0.3, 0.3 };

// static int _equal_2d(int rows, int cols, double **a, double **b)
// {
//   for (int i = 0; i < rows; i++) {
//     for (int j = 0; j < cols; j++) {
//       if (a[i][j] != b[i][j]) {
//         printf("DIFF: %5f %5f\n", a[i][j], b[i][j]);
//         return 0;
//       }
//     }
//   }
//   return 1;
// }

// static int _test1()
// {
//   INIT_ARR_2D(a1, a1_vals);
//   INIT_ARR_2D(b1, b1_vals);
//   INIT_ARR_2D(c1, c1_vals);

//   struct Matrix *a = new_matrix(2, 1, a1);
//   struct Matrix *b = new_matrix(2, 2, b1);
//   struct Matrix *c = b->dot(b, a);

//   return _equal_2d(c->rows, c->cols, c->vals, c1);
// }

// static int _test2() 
// {
//   INIT_ARR_2D(a2, a2_vals);
//   INIT_ARR_2D(b2, b2_vals);
//   INIT_ARR_2D(c2, c2_vals);

//   struct Matrix *a = new_matrix(2, 1, a2);
//   struct Matrix *b = new_matrix(2, 1, b2);
//   struct Matrix *c = b->add(b, a);

//   return _equal_2d(c->rows, c->cols, c->vals, c2);
// }

// static int _test3()
// {
//   a3 = (int *) malloc(sizeof(int) * LEN(a3_vals));
//   SET(a3, a3_vals, LEN(a3_vals));

//   struct Net *net = new_net(b3, c3, a3, LEN(a3_vals), sigmoid);

//   INIT_ARR(d3, d3_vals);
//   int out = net->forward(net, d3);
//   printf("OUT: %3d\n", out);
//   return 1; // didn't crash
// }

// static int _test4()
// {
//   a4 = (int *) malloc(sizeof(int) * LEN(a4_vals));
//   SET(a4, a4_vals, LEN(a4_vals));

//   struct Net *net = new_net(b4, c4, a4, LEN(a4_vals), sigmoid);

//   INIT_ARR(d4, d4_vals);
//   int out = net->forward(net, d4);
//   printf("OUT: %3d\n", out);
//   return 1; // didn't crash
// }


// int test_matrix() 
// {
//   FPI tests[] = { _test1, _test2 };
//   for (int i = 0; i < LEN(tests); i++) {
//     printf("%10s test: %3d\n", "Matrix", i);
//     if (!tests[i]()) {
//       puts("FAILED");
//       return 0;
//     }
//   }
//  return 1;
// }

// int test_network()
// {
//   FPI tests[] = { _test3, _test4 };
//   for (int i = 0; i < LEN(tests); i++) {
//     printf("%10s test: %3d\n", "Network", i);
//     if (!tests[i]()) {
//       puts("FAILED");
//       return 0;
//     }
//   }
  
//  return 1;
// }