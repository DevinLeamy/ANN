#ifndef VECTOR_H
#define VECTOR_H

enum FillType {
  FILL_RANDOM,
  FILL_ZERO
};

typedef double *Vector;

struct _SVector {
  int length; 
  Vector vals;
};

typedef struct _SVector* SVector;

Vector new_vector(int, enum FillType);
SVector new_svector(int, enum FillType);

SVector copy_svector(SVector);
void display_svector(SVector); 
void display_vector(int, Vector); 

void free_vector(Vector);
void free_svector(SVector);



#endif