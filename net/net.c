#include "./net.h"
#include "../matrix/matrix.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// static int _forward(struct Net *self, double *input) 
// {
//   // format input
//   double **input_f = init_2d(self->input_n, 1, RANDOM_INIT);
//   for (int i = 0; i < self->input_n; i++)
//     input_f[i][0] = input[i];

//   // result matrix
//   struct Matrix *x = new_matrix(self->input_n, 1, input_f); 

//   for (int i = 0; i < LAYERS(self) - 1; i++) {
//     assert(x->cols == 1);

//     struct Matrix *wgt_mtx = (self->weights)[i];
//     struct Matrix *bias_mtx = (self->biases)[i];

//     // dot(weights, prev)
//     struct Matrix *new_x = wgt_mtx->dot(wgt_mtx, x); 
//     x->free(x);
//     x = NULL;

//     // add biases
//     x = new_x->add(new_x, bias_mtx);

//     // activation function
//     x->apply(x, self->act);

//     new_x->free(new_x); 
//     new_x = NULL;
// }

//   assert(x->cols == 1);

//   // idx of max value
//   int res = 0;
//   double c_max = (x->vals)[0][0];

//   for (int i = 0; i < x->rows; i++) {
//     if (c_max < (x->vals)[i][0]) {
//       c_max = (x->vals)[i][0];
//       res = i;
//     }
//   }

//   x->free(x);
//   x = NULL;

//   return res;
// }

static SMatrix _new_weights(int p_nodes, int n_nodes) {
  SMatrix weights = new_smatrix(n_nodes, p_nodes, FILL_RANDOM);

  return weights;
}

static SMatrix _new_biases(int nodes) {
  SVector biases = new_svector(nodes, FILL_RANDOM);
  return biases;
}

static Layer _new_layer(int p_nodes, int n_nodes, ActivationFn activation) {
  Layer layer = (Layer) malloc(sizeof(struct Layer));
  layer->activation = activation;
  layer->weights = _new_weights(p_nodes, n_nodes);
  layer->biases = _new_biases(n_nodes);

  return layer;
}

// constructor
Net new_net(int *layers) {
  Net net = (Net) malloc(sizeof(struct Net));

  net->IN = layers[0];
  net->H1 = layers[1];
  net->H2 = layers[2];
  net->OUT = layers[3];

  net->l1 = _new_layer(net->IN, net->H1, sigmoid_vector);
  net->l2 = _new_layer(net->H1, net->H2, sigmoid_vector);
  net->l3 = _new_layer(net->H2, net->OUT, softmax_vector);

  return net;
}