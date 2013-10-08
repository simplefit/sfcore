#include <iostream>
#include <stdexcept>

#include "function.hxx"


double sum(unsigned len, double * ele)
{
  double res(0.);
  for (unsigned i = 0; i < len; ++i) {
    res += ele[i];
  }
  return res;
}

int main()
{
  double array[3] = {1, 2, 3};
  function myfunc(3, array, sum);

  std::cout << "automatic conversion: myfunc: " << myfunc << std::endl;

  double * array2 = myfunc.params().second;
  array2[2] = 4;
  array2[1] = 3;
  std::cout << "parameter change (direct): myfunc: " << myfunc << std::endl;

  try {
    myfunc.set_param(1, 2);
    myfunc.set_param(2, 3);
    std::cout << "parameter change (setter): myfunc: " << myfunc << std::endl;
    myfunc.set_param(3, 5);
  } catch (std::out_of_range &exc) {
    std::cout << "exception handling: "<< exc.what();
  }

  return 0;
}
