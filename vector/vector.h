#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>

typedef double *Vector;

enum FillType {
  FILL_RANDOM,
  FILL_ZERO
};

struct SVector {
  int length; 
  Vector vals;
};

typedef struct SVector * SVector;


Vector new_vector(int, enum FillType);
SVector new_svector(int, enum FillType);

void display_vector(int, Vector); 

void free_vector(int, Vector);
void free_svector(SVector);



#endif