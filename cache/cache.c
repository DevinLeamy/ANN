#include "cache.h"


CLayer new_clayer() {
  CLayer layer = (CLayer) malloc(sizeof(struct CLayer));
  layer->activated = NULL;
  layer->activated_grads = NULL;
  layer->inactivated = NULL;
  layer->inactivated_grads = NULL;
  layer->bias_grads = NULL;
  layer->weight_grads = NULL;

  return layer;
}

void free_clayer(CLayer layer) {
  if (layer == NULL) return;

  free_svector(layer->activated);
  free_svector(layer->activated_grads);
  free_svector(layer->inactivated);
  free_svector(layer->inactivated_grads);
  free_svector(layer->bias_grads);
  free_smatrix(layer->weight_grads);
  free(layer);
}

void free_cache(Cache cache) {
  free_clayer(cache->l0);
  free_clayer(cache->l1);
  free_clayer(cache->l2);
  free_clayer(cache->l3);
  free(cache);
}

// constructor
Cache new_cache() {
  Cache cache = (Cache) malloc(sizeof(struct Cache));
  cache->l0 = new_clayer();
  cache->l1 = new_clayer();
  cache->l2 = new_clayer();
  cache->l3 = new_clayer();

  return cache;
}