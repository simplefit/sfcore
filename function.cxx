#include <stdexcept>
#include <string>

#include "function.hxx"


function::operator double () const
{
  return _fptr(_num, _args);
}

void function::set_param(unsigned idx, double val)
{
  if (idx >= _num)
    throw std::out_of_range("Index out of range, " + std::to_string(idx)
			    + " >= " + std::to_string(_num) + "\n");
  _args[idx] = val;
}

std::pair<int, double *> function::params() const
{
  return std::pair<int, double *> (_num, _args);
}
