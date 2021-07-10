#ifndef MATH_H
#define MATH_H

typedef double (*Activation)(double x);

double sigmoid(double);
double random_dbl();
void math_init();

#endif
