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

  std::cout << "automatic conversion: myfunc: " << myfunc << std::endl;

  auto& vars = myfunc.components();
  vars[1] = fnbase_ptr(new variable(3));
  vars[2] = fnbase_ptr(new variable(5));
  std::cout << "parameter change (direct): myfunc: " << myfunc << std::endl;

  try {
    myfunc.replace(0, fnbase_ptr(new variable(2)));
    myfunc.replace(1, fnbase_ptr(new variable(4)));
    myfunc.replace(2, fnbase_ptr(new variable(6)));
    std::cout << "parameter change (setter): myfunc: " << myfunc << std::endl;
    myfunc.replace(3, fnbase_ptr(new variable(2)));
  } catch (std::out_of_range &exc) {
    std::cout << "exception handling: "<< exc.what() << std::endl;
  }

  return 0;
}
