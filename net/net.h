#ifndef NET_H
#define NET_H

#include "../math/math.h"
#include "../cache/cache.h"

typedef SVector (*ActivationFn)(SVector, int);

struct Layer {
  SMatrix weights;
  SVector biases;
  ActivationFn activation;
};

typedef struct Layer *Layer;

struct Net {
  int IN, OUT, H1, H2;
  Layer l1;
  Layer l2;
  Layer l3;
};

typedef struct Net *Net;

Net new_net(int *);
Cache forward(Net, SVector);
Cache backwards(Net, Cache, SVector);

#endif