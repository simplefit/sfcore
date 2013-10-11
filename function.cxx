// #include <stdexcept>
// #include <string>

#include "function.hxx"


function::operator double () const
{
  return _fptr(_args);
}

void function::replace(const unsigned idx, const fnbase_ptr arg)
{
  // if (idx >= _args.size())
  //   throw std::out_of_range("Index out of range, " + std::to_string(idx)
  // 			    + " >= " + std::to_string(_args.size()) + "\n");
  _args.at(idx) = arg;
}

auto function::components() -> fnbase_vec &
{
  return _args;
}
