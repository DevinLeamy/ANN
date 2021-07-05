// #include "./layer.h"
// #include "./node.h"

// #include <stdlib.h>


// static void _activate(struct Layer *self)
// {
//   for (int i = 0; i < self->cnt; i++)
//     self->activation(&self->nodes[i]);
// }

// // constructor
// struct Layer *new_layer(Activation activation, int cnt)
// {
//   struct Layer *layer = (struct Layer *) malloc(sizeof(struct Layer));
//   layer->activation = activation;
//   layer->activate = _activate;
//   layer->cnt = cnt;
//   layer->nodes = (struct Node *) malloc(sizeof(struct Node) * cnt);
//   for (int i = 0; i < cnt; i++)
//     layer->nodes[i] = new_node();
//   return layer;
// }

// // free memory
// void free_layer(struct Layer *layer) 
// {
//   free(layer->nodes);
//   free(layer);
// }