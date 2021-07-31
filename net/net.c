#include "net.h"
#include "../matrix/matrix.h"
#include "../vector/vector.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

SVector get_inactivated(SVector previous_activated, SMatrix weights, SVector biases) {
  SVector dot_product = dot_matrix_vector(weights, previous_activated); 
  dot_product = add_vectors(dot_product, biases, MODIFY_TRUE);

  return dot_product;
}

SVector get_activated(SVector previous_inactivated, ActivationFn activation) {
  return activation(previous_inactivated, DERIVATIVE_FALSE); 
}

Cache forward(Net net, SVector x) {
  Cache cache = new_cache();
  CLayer l0 = cache->l0; CLayer l1 = cache->l1;
  CLayer l2 = cache->l2; CLayer l3 = cache->l3;

  l0->activated = copy_svector(x);

  l1->inactivated = get_inactivated(l0->activated, net->l1->weights, net->l1->biases);
  l1->activated = get_activated(l1->inactivated, net->l1->activation);

  l2->inactivated = get_inactivated(l1->activated, net->l2->weights, net->l2->biases);
  l2->activated = get_activated(l2->inactivated, net->l2->activation);

  l3->inactivated = get_inactivated(l2->activated, net->l3->weights, net->l3->biases);
  l3->activated = get_activated(l3->inactivated, net->l3->activation);

  return cache;
}

void apply_weight_gradients(SMatrix weights, SMatrix weight_grads, double learning_rate) {
  scale_matrix(weight_grads, learning_rate, MODIFY_TRUE);
  sub_matrices(weights, weight_grads, MODIFY_TRUE);
}

void apply_bias_gradients(SVector biases, SVector bias_grads, double learning_rate) {
  scale_vector(bias_grads, learning_rate, MODIFY_TRUE);
  sub_vectors(biases, bias_grads, MODIFY_TRUE);
}

void apply_gradients(Net net, Cache cache) {
  apply_weight_gradients(net->l1->weights, cache->l1->weight_grads, net->learning_rate);
  apply_weight_gradients(net->l2->weights, cache->l2->weight_grads, net->learning_rate);
  apply_weight_gradients(net->l3->weights, cache->l3->weight_grads, net->learning_rate);

  apply_bias_gradients(net->l1->biases, cache->l1->bias_grads, net->learning_rate);
  apply_bias_gradients(net->l2->biases, cache->l2->bias_grads, net->learning_rate);
  apply_bias_gradients(net->l3->biases, cache->l3->bias_grads, net->learning_rate);
}

// only relavent to the last layer
SVector get_derivative_cost_wrt_activated(SVector y_hat, SVector y) {
  SVector difference = sub_vectors(y_hat, y, MODIFY_FALSE);
  SVector scaled = scale_vector(difference, 2.0, MODIFY_TRUE);

  return scaled;
}

SVector get_derivate_activated_wrt_inactivated(SVector inactivated, ActivationFn activation) {
  return activation(inactivated, DERIVATIVE_TRUE);
}

SVector get_bias_grads(SVector activated_wrt_inactivated, SVector cost_wrt_activated) {
  return multiply_vectors(activated_wrt_inactivated, cost_wrt_activated, MODIFY_FALSE); 
}

SMatrix get_weight_grads(SVector previous_activated, SVector bias_grads) {
  return outer_product(bias_grads, previous_activated);
}

SVector get_activated_grads(SMatrix weights, SVector bias_grads) {
  SMatrix weights_transposed = transpose_matrix(weights);
  SVector activated_grads = dot_matrix_vector(weights_transposed, bias_grads);

  free_smatrix(weights_transposed);
  return activated_grads; 
}

void backwards(Net net, Cache cache, SVector y) {
  SVector y_hat = cache->l3->activated; 
  CLayer l0 = cache->l0; CLayer l1 = cache->l1;
  CLayer l2 = cache->l2; CLayer l3 = cache->l3; 

  // create a function for each layer
  {
    l3->activated_grads = get_derivative_cost_wrt_activated(y_hat, y); 
    l3->inactivated_grads = get_derivate_activated_wrt_inactivated(l3->inactivated, net->l3->activation);

    l3->bias_grads = get_bias_grads(l3->inactivated_grads, l3->activated_grads);
    l3->weight_grads = get_weight_grads(l2->activated, l3->bias_grads);
  }

  {
    l2->activated_grads = get_activated_grads(net->l3->weights, l3->bias_grads); 
    l2->inactivated_grads = get_derivate_activated_wrt_inactivated(l2->inactivated, net->l2->activation);

    l2->bias_grads = get_bias_grads(l2->inactivated_grads, l2->activated_grads);
    l2->weight_grads = get_weight_grads(l1->activated, l2->bias_grads);
  }

  {
    l1->activated_grads = get_activated_grads(net->l2->weights, l2->bias_grads); 
    l1->inactivated_grads = get_derivate_activated_wrt_inactivated(l1->inactivated, net->l1->activation);

    l1->bias_grads = get_bias_grads(l1->inactivated_grads, l1->activated_grads);
    l1->weight_grads = get_weight_grads(l0->activated, l1->bias_grads);
  }
}

double compute_loss(SVector y_hat, SVector y) {
  SVector diff = sub_vectors(y_hat, y, MODIFY_FALSE);
  square_vector(diff, MODIFY_TRUE); 
  double loss = sum_vector(diff);

  free_svector(diff);
  return loss;
}

static SMatrix _new_weights(int p_nodes, int n_nodes) {
  SMatrix weights = new_smatrix(n_nodes, p_nodes, FILL_RANDOM);
  return weights;
}

static SVector _new_biases(int nodes) {
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

int *get_batch_indices(int example_cnt, int batch_size) {
  int *indices = (int *) malloc(sizeof(int) * batch_size);
  for (int i = 0; i < batch_size; i++)
    indices[i] = random_int(example_cnt); 
  return indices;
}

void display_results(Net net, SVector guesses, SVector accuracy_vec, SVector loss_vec) {
  printf("Accuracy: %3.2f%%\n", mean_vector(accuracy_vec));
  printf("Loss:   : %3.2f\n", mean_vector(loss_vec));
  for (int i = 0; i < net->OUT; i++)
    printf("%d: %d ", i, (int) guesses->vals[i]);
  puts("\n");
}

void test(Net net, struct MNIST MNIST) {
  SVector *inputs  = MNIST.test_images;
  SVector *outputs = MNIST.test_labels;

  SVector accuracy_vec = new_svector(TEST_EXAMPLE_CNT, FILL_ZERO);
  SVector loss_vec = new_svector(TEST_EXAMPLE_CNT, FILL_ZERO);
  SVector guesses = new_svector(net->OUT, FILL_ZERO);

  for (int i = 0; i < TEST_EXAMPLE_CNT; i++) {
    SVector x = inputs[i];
    SVector y = outputs[i];

    Cache cache = forward(net, x);

    double loss = compute_loss(cache->l3->activated, y);
    int guess = argmax_vector(cache->l3->activated);
    int ans   = argmax_vector(y);

    accuracy_vec->vals[i] = guess == ans;
    loss_vec->vals[i] = loss;
    guesses->vals[guess]++;

    free_cache(cache);
  }
  display_results(net, guesses, accuracy_vec, loss_vec);

  free_svector(accuracy_vec);
  free_svector(loss_vec);
  free_svector(guesses);
}

void train(Net net, struct MNIST MNIST, int epochs, int batch_sz) {
  SVector *inputs  = MNIST.train_images;
  SVector *outputs = MNIST.train_labels;
  for (int epoch = 0; epoch < epochs; epoch++) {
    int *batch_indices = get_batch_indices(TRAIN_EXAMPLE_CNT, batch_sz);
    for (int i = 0; i < batch_sz; i++) {
      SVector x = inputs[batch_indices[i]];
      SVector y = outputs[batch_indices[i]];

      Cache cache = forward(net, x);
      backwards(net, cache, y);
      apply_gradients(net, cache);

      free_cache(cache);
    }
    if (epoch % 100 == 0) {
      printf("EPOCH: #%d\n", epoch);
      test(net, MNIST);
    }

    free(batch_indices);
  }
}

// constructor
Net new_net(int *layers, double learning_rate) {
  Net net = (Net) malloc(sizeof(struct Net));

  net->learning_rate = learning_rate;
  net->IN = layers[0];
  net->H1 = layers[1];
  net->H2 = layers[2];
  net->OUT = layers[3];

  net->l1 = _new_layer(net->IN, net->H1, sigmoid_vector);
  net->l2 = _new_layer(net->H1, net->H2, sigmoid_vector);
  net->l3 = _new_layer(net->H2, net->OUT, softmax_vector);

  return net;
}