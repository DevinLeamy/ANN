#include "matrix/matrix.h"
#include "vector/vector.h"
#include "mnist/mnist.h"
#include "math/math.h"
#include "net/net.h"

int LAYERS[] = { 784, 128, 64, 10 };
double LEARNING_RATE = 0.01;
int EPOCHS = 10000; 
int BATCH_SIZE = 128;
 
int main()
{
  initialize_math();
  initialize_mnist();

  Net net = new_net(LAYERS, LEARNING_RATE);
  train(net, MNIST, EPOCHS, BATCH_SIZE);

  free_mnist();
  return 0;
}