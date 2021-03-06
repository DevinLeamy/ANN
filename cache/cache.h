#ifndef CACHE_H
#define CACHE_H

#include "../matrix/matrix.h"
#include "../vector/vector.h"
#include <stdlib.h>

struct CLayer {
  SVector activated; 
  SVector activated_grads;
  SVector inactivated;
  SVector inactivated_grads;
  SVector bias_grads;
  SMatrix weight_grads;
};

typedef struct CLayer *CLayer;

CLayer new_clayer();
void free_clayer();

struct Cache {
  CLayer l0;
  CLayer l1;
  CLayer l2;
  CLayer l3; 
};

typedef struct Cache *Cache;

Cache new_cache();
void free_cache();

#endif 