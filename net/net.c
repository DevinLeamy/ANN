#include "./net.h"
#include "../matrix/matrix.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef int (*Forward)(struct Net *self);

static int _forward(struct Net *self, double *input) 
{
  // format input
  double **input_f = init_2d(self->input_n, 1, RANDOM_INIT);
  for (int i = 0; i < self->input_n; i++)
    input_f[i][0] = input[i];

  // result matrix
  struct Matrix *x = new_matrix(self->input_n, 1, input_f); 

  for (int i = 0; i < LAYERS(self) - 1; i++) {
    assert(x->cols == 1);

    struct Matrix *wgt_mtx = (self->weights)[i];
    struct Matrix *bias_mtx = (self->biases)[i];

    // dot(weights, prev)
    struct Matrix *new_x = wgt_mtx->dot(wgt_mtx, x); 
    x->free(x);
    x = NULL;

    // add biases
    x = new_x->add(new_x, bias_mtx);

    // activation function
    x->apply(x, self->act);

    new_x->free(new_x); 
    new_x = NULL;
}

  assert(x->cols == 1);

  // idx of max value
  int res = 0;
  double c_max = (x->vals)[0][0];

  for (int i = 0; i < x->rows; i++) {
    if (c_max < (x->vals)[i][0]) {
      c_max = (x->vals)[i][0];
      res = i;
    }
  }

  x->free(x);
  x = NULL;

  return res;
}

// create weights matrices
static struct Matrix **_create_weights(struct Net *self) 
{
  struct Matrix **weights = (struct Matrix **) malloc(sizeof(struct Matrix *) * (LAYERS(self) - 1));
  int prev_nds = self->input_n;
  for (int i = 1; i < LAYERS(self); i++) {
    int nds = (OUTPUT_LY(self, i))? self->output_n : (self->hidden_n)[i - 1];

    // create matrix with random values
    weights[i - 1] = new_matrix(nds, prev_nds, NULL);
    prev_nds = nds;
  }

  return weights;
}

// create biase matrices
static struct Matrix **_create_biases(struct Net *self) 
{
  struct Matrix **biases = (struct Matrix **) malloc(sizeof(struct Matrix *) * (LAYERS(self) - 1));
  for (int i = 1; i < LAYERS(self); i++) {
    int nds = (OUTPUT_LY(self, i))? self->input_n : self->hidden_n[i - 1]; 

    // create matrix with random values
    biases[i - 1] = new_matrix(nds, 1, NULL);
  }

  return biases;
}

// constructor
struct Net *new_net(int input_n, int output_n, int *hidden_n, int hidden_cnt, Activation act) 
{
  struct Net *net = (struct Net *) malloc(sizeof(struct Net));
  net->input_n = input_n;
  net->output_n = output_n;

  net->hidden_n = (int *) malloc(sizeof(int) * hidden_cnt);
  memcpy(net->hidden_n, hidden_n, sizeof(int) * hidden_cnt);

  net->hidden_cnt = hidden_cnt;

  net->biases = _create_biases(net);
  net->weights = _create_weights(net);
  net->forward = _forward;
  net->act = act;
  return net;
}