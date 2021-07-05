#include "./math.h"
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
  srand(time(NULL)); // should only be called once
  long x = rand(); 
  double x_nor = _normalize(0l, RAND_MAX, x);
  return x_nor;
}