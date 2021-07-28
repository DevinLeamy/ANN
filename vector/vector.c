#include "vector.h"

double initialize_value(enum FillType fill_type) {
  if (fill_type == FILL_RANDOM)
    return random_double();
  return 0.0;
}

void display_vector(int length, Vector vector) {
  for (int i = 0; i < length; i++) 
    printf("%5.3f ", vector[i]);
  puts("\n");
}

Vector new_vector(int length, enum FillType fill_type) {
  Vector vector = (Vector) malloc(sizeof(double) * length);
  for (int i = 0; i < vector; i++)
    vector[i] = initialize_value(fill_type);
  return vector;
}

SVector new_svector(int length, enum FillType fill_type) {
  SVector vector = (SVector) malloc(sizeof(struct SVector));
  vector->length = length;
  vector->vals = new_vector(length, fill_type);

  return vector;
}