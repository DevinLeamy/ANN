#ifndef TEST_H
#define TEST_H

#define LEN(arr) sizeof arr / sizeof arr[0]

#define SET_2D(arr, src, rows, cols) \
  for (int i = 0; i < rows; i++) \
    for (int j = 0; j < cols; j++) \
      arr[i][j] = src[i][j];

#define INIT_ARR_2D(arr, src) \
  arr = init_2d(LEN(src), LEN(src[0]), RANDOM_INIT); \
  SET_2D(arr, src, LEN(src), LEN(src[0]));

#define SET(arr, src, len) \
  for (int i = 0; i < len; i++) \
    arr[i] = src[i];

#define INIT_ARR(arr, src) \
  arr = init_arr(LEN(src), RANDOM_INIT); \
  SET(arr, src, LEN(src));



typedef int (*FPI)();

int test_matrix();
int test_network();
#endif 
