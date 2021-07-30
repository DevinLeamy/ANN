#ifndef MNIST_H
#define MNIST_H

#include "../vector/vector.h"

#define TRAIN_IMAGES_PATH "res/train_images.gz"
#define TRAIN_LABELS_PATH "res/train_labels.gz"
#define TEST_IMAGES_PATH  "res/test_images.gz"
#define TEST_LABELS_PATH  "res/test_labels.gz"

#define TRAIN_IMAGES_LENGTH (60000 * 28 * 28 + 16)
#define TEST_IMAGES_LENGTH  (10000 * 28 * 28 + 16)

#define IMAGE_DATA_BUFFER 16
#define LABEL_DATA_BUFFER 8

#define TRAIN_EXAMPLE_CNT 60000
#define TEST_EXAMPLE_CNT  10000

#define IMAGE_SIZE (28 * 28)
#define LABEL_SIZE (10)

extern struct MNIST MNIST;

struct MNIST {
  SVector *train_images;
  SVector *train_labels;
  SVector *test_images;
  SVector *test_labels;
};

// global mnist
struct MNIST mnist;

void mnist_init();

#endif