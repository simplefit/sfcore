#include <iostream>
#include <cassert>
#include <stdexcept>

#include "variable.hxx"
#include "coreutils.hxx"


double sum(std::vector<double> & args)
{
  double res(0.);
  for (unsigned i = 0; i < args.size(); ++i) {
    res += double(args[i]);
  }
  return res;
}

int main()
{
  double array[3] = {1, 2, 3};
  auto myfunc1 = fnbase_ptr(&make_function(sum, 3, array)); // 1+2+3
  auto myfunc2 = fnbase_ptr(&make_function(sum, 3, array)); // 1+2+3
  fnbase_vec vars {myfunc1, myfunc2};
  function grandsum(sum, vars); // 6+6
  assert(12 == grandsum);
  return 0;
}
