#ifndef MATRIX_H
#define MATRIX_H

struct Matrix {
  int rows, cols;
  double **vals;
  struct Matrix *(*dot)(struct Matrix*, struct Matrix*);
  void (*free)(struct Matrix*); 
};

struct Matrix *new_matrix(int row, int col, double **vals);
void display_matrix(struct Matrix *matrix);
double **init_2d(int row, int col);

#endif