#include "matrix/matrix.h"
#include "vector/vector.h"
#include "mnist/mnist.h"
#include "math/math.h"
#include "net/net.h"

int main()
{
  math_init();
  mnist_init();

  int layers[] = { 784, 128, 64, 10 };
  double learning_rate = 0.005;
  Net net = new_net(layers, learning_rate);

  train(net, MNIST, 1000, 128);
  // test(net, MNIST);
  return 0;
}