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
  cache->l0->activated = copy_svector(x);

  // puts("forward_start");
  cache->l1->inactivated = get_inactivated(cache->l0->activated, net->l1->weights, net->l1->biases);
  cache->l1->activated = get_activated(cache->l1->inactivated, net->l1->activation);

  cache->l2->inactivated = get_inactivated(cache->l1->activated, net->l2->weights, net->l2->biases);
  cache->l2->activated = get_activated(cache->l2->inactivated, net->l2->activation);

  cache->l3->inactivated = get_inactivated(cache->l2->activated, net->l3->weights, net->l3->biases);
  cache->l3->activated = get_activated(cache->l3->inactivated, net->l3->activation);
  // puts("forward_end");

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
  // puts("back_start");
  SVector y_hat = cache->l3->activated; 

  // create a function for each layer
  {
    cache->l3->activated_grads = get_derivative_cost_wrt_activated(y_hat, y); 
    cache->l3->inactivated_grads = get_derivate_activated_wrt_inactivated(cache->l3->inactivated, net->l3->activation);

    cache->l3->bias_grads = get_bias_grads(cache->l3->inactivated_grads, cache->l3->activated_grads);
    cache->l3->weight_grads = get_weight_grads(cache->l2->activated, cache->l3->bias_grads);
  }

  {
    cache->l2->activated_grads = get_activated_grads(net->l3->weights, cache->l3->bias_grads); 
    cache->l2->inactivated_grads = get_derivate_activated_wrt_inactivated(cache->l2->inactivated, net->l2->activation);

    cache->l2->bias_grads = get_bias_grads(cache->l2->inactivated_grads, cache->l2->activated_grads);
    cache->l2->weight_grads = get_weight_grads(cache->l1->activated, cache->l2->bias_grads);
  }

  {
    cache->l1->activated_grads = get_activated_grads(net->l2->weights, cache->l2->bias_grads); 
    cache->l1->inactivated_grads = get_derivate_activated_wrt_inactivated(cache->l1->inactivated, net->l1->activation);

    cache->l1->bias_grads = get_bias_grads(cache->l1->inactivated_grads, cache->l1->activated_grads);
    cache->l1->weight_grads = get_weight_grads(cache->l0->activated, cache->l1->bias_grads);
  }
  // puts("back_end");
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
    indices[i] = rand() % example_cnt;
  return indices;
}

double test(Net net, struct MNIST MNIST) {
  SVector *inputs  = MNIST.test_images;
  SVector *outputs = MNIST.test_labels;

  int correct_guesses = 0;
  SVector guesses = new_svector(10, FILL_ZERO);

  for (int i = 0; i < TEST_EXAMPLE_CNT; i++) {
    SVector x = inputs[i];
    SVector y = outputs[i];

    Cache cache = forward(net, x);

    int guess = argmax_vector(cache->l3->activated);
    int ans   = argmax_vector(y);

    if (guess == ans)
      correct_guesses++;
    guesses->vals[guess]++;
  }

  double accuracy = percentage(correct_guesses, TEST_EXAMPLE_CNT); 
  printf("Accuracy: %0.2f\n", accuracy);
  display_vector(guesses->length, guesses->vals);

  free_svector(guesses);
  return accuracy;
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
      display_vector(cache->l1->inactivated->length, cache->l1->inactivated->vals);
      // display_vector(cache->l3->activated->length, cache->l3->activated->vals);

      backwards(net, cache, y);
      apply_gradients(net, cache);

      free_cache(cache);
    }
    if (epoch % 10 == 0)
      test(net, MNIST);
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
  // net->l3 = _new_layer(net->H2, net->OUT, sigmoid_vector);
  net->l3 = _new_layer(net->H2, net->OUT, softmax_vector);

  return net;
}