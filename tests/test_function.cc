#include <iostream>
#include <stdexcept>

#include "function.hxx"
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

  function &myfunc = make_function(sum, 3, array);

  std::cout << "automatic conversion: myfunc: 1+2+3 = " << myfunc << std::endl;

  auto& vars = myfunc.components();
  vars[1] = fnbase_ptr(new variable(3));
  vars[2] = fnbase_ptr(new variable(5));
  std::cout << "parameter change (direct): myfunc: 1+3+5 = " << myfunc << std::endl;

  try {
    for (unsigned i = 0; i < 3; ++i) {
      myfunc.replace(i, new variable((i+1) * 2));
    }
    std::cout << "parameter change (setter): myfunc: 2+4+6 = " << myfunc << std::endl;
    myfunc.replace(3, new variable(2));
  } catch (std::out_of_range &exc) {
    std::cout << "exception handling: "<< exc.what() << std::endl;
  }

  return 0;
}
