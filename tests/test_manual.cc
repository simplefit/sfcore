#include <iostream>
#include <cassert>
#include <stdexcept>

#include "variable.hxx"
#include "coreutils.hxx"

#include "testutils.hh"


int main()
{
  double array[3] = {1, 2, 3};
  auto vararray = pod_to_variable(3, array);
  auto myfunc1 = std::make_shared<function>(sum, vararray); // 1+2+3
  auto myfunc2 = std::make_shared<function>(sum, vararray); // 1+2+3
  fnbase_ptr_vec vars {myfunc1, myfunc2};
  function grandsum(sum, vars); // 6+6
  assert(12 == grandsum);
  return 0;
}
