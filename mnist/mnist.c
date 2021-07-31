#include "mnist.h"
#include <zlib.h>
#include <stdlib.h>
#include <stdio.h>
#include "../matrix/matrix.h"

struct MNIST MNIST;

static uint8_t *_read_raw_data(char *path, unsigned long file_length) {
  gzFile gz_file = gzopen(path, "rb");
  if (gz_file == NULL) return NULL;

  uint8_t *raw_image_data = (uint8_t *) malloc(sizeof(uint8_t) * file_length);
  gzread(gz_file, raw_image_data, file_length);

  return raw_image_data;
}

static SVector *_preprocess_image_data(uint8_t *raw_image_data, int image_cnt) {
  SVector *parsed_image_data = (SVector *) malloc(sizeof(SVector) * image_cnt);

  for (int i = 0; i < image_cnt; i++) {
    SVector image = new_svector(IMAGE_SIZE, FILL_ZERO);
    for (int j = 0; j < IMAGE_SIZE; j++)
      image->vals[j] = raw_image_data[IMAGE_DATA_BUFFER + i * IMAGE_SIZE + j] / 255.0;

    parsed_image_data[i] = image;
  }
  return parsed_image_data;
}

static SVector *_preprocess_label_data(uint8_t *raw_label_data, int label_cnt) {
  SVector *parsed_label_data = (SVector *) malloc(sizeof(SVector) * label_cnt);

  for (int i = 0; i < label_cnt; i++) {
    SVector label = new_svector(LABEL_SIZE, FILL_ZERO);
    label->vals[raw_label_data[LABEL_DATA_BUFFER + i]] = 1.0; 

    parsed_label_data[i] = label;
  }
  return parsed_label_data;
}

static SVector *_parse_image_file(char *path, int image_cnt) {
  unsigned long file_length = image_cnt * IMAGE_SIZE + IMAGE_DATA_BUFFER;

  uint8_t *raw_image_data = _read_raw_data(path, file_length); 
  SVector *parsed_image_data = _preprocess_image_data(raw_image_data, image_cnt);

  free(raw_image_data);
  return parsed_image_data;
}


static SVector *_parse_label_file(char *path, int label_cnt) {
  unsigned long file_length = label_cnt + IMAGE_DATA_BUFFER; 

  uint8_t *raw_label_data = _read_raw_data(path, file_length);
  SVector *parsed_label_data = _preprocess_label_data(raw_label_data, label_cnt);

  free(raw_label_data);
  return parsed_label_data;
}


void mnist_init() {
  MNIST.train_images = _parse_image_file(TRAIN_IMAGES_PATH, TRAIN_EXAMPLE_CNT);
  MNIST.test_images = _parse_image_file(TEST_IMAGES_PATH, TEST_EXAMPLE_CNT);

  MNIST.train_labels = _parse_label_file(TRAIN_LABELS_PATH, TRAIN_EXAMPLE_CNT);
  MNIST.test_labels = _parse_label_file(TEST_LABELS_PATH, TEST_EXAMPLE_CNT);
}