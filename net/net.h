#ifndef NET_H
#define NET_H

#include "../matrix/matrix.h"
#include "../math/math.h"

#define BIAS_MTX(self, i) (self->biases)[i]
#define WGT_MTX(self, i) (self->weights)[i]

#define LAYERS(net) (2 + net->hidden_cnt)

#define INPUT_LY(net, depth) (depth == 0)
#define OUTPUT_LY(net, depth) (depth == LAYERS(net) - 1)
#define HDN_LY(net, depth) !INPUT_LY(net, depth) && !OUTPUT_LY(net, depth)

struct Net {
  int input_n, output_n, *hidden_n, hidden_cnt;
  struct Matrix **weights; 
  struct Matrix **biases;
  Activation act;
  int (*forward)(struct Net *self, double *input);
};

struct Net *new_net(int input_n, int output_n, int *hidden_n, int hidden_cnt, Activation act);

#endif