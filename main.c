#include "./matrix/matrix.h"
#include "./tests/tests.h"
#include "./math/math.h"

int main()
{
  // init
  math_init();


  // testing
  test_matrix();
  test_network();
  return 0;
}