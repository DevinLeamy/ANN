#ifndef MNIST_H
#define MNIST_H

// asset paths
#define MNIST_PATH "../res/";
#define TRN_IMG_PATH MNIST_PATH "training-images"
#define TRN_LBL_PATH MNIST_PATH "training-labels"
#define TST_IMG_PATH MNIST_PATH "testing-images"
#define TST_LBL_PATH MNIST_PATH "testing-labels"

struct MNIST {
  double ***train_imgs;
  double **train_lbls;
  double ***test_imgs;
  double **test_lbls;
};

// global mnist
struct MNIST mnist;

void mnist_init();

#endif