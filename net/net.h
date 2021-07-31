#ifndef NET_H
#define NET_H

#include "../math/math.h"
#include "../cache/cache.h"
#include "../mnist/mnist.h" 

typedef SVector (*ActivationFn)(SVector, int);

struct Layer {
  SMatrix weights;
  SVector biases;
  ActivationFn activation;
};

typedef struct Layer *Layer;

struct Net {
  int IN, OUT, H1, H2;
  double learning_rate;
  Layer l1;
  Layer l2;
  Layer l3;
};

typedef struct Net *Net;

Net new_net(int *, double learning_rate);
Cache forward(Net, SVector);
void backwards(Net, Cache, SVector);
void train(Net, struct MNIST, int, int);
void test(Net, struct MNIST);

#endif