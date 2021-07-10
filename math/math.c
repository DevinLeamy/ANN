#include "./math.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

// normalize on range (-1, 1)
static double _normalize(long min_x, long max_x, long x)
{
  return (double) (x - min_x) / (max_x - min_x);
}

// generate random double on (-1, 1)
double random_dbl()
{
  long x = rand(); 
  double x_nor = _normalize(0l, RAND_MAX, x);
  return x_nor;
}

// sigmoid
double sigmoid(double x) 
{
  return 1.0 / (1.0 + exp(-1.0 * x));
}


void math_init() 
{
  // init random
  srand(time(NULL));
}