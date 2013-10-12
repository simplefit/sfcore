#include <stdexcept>
#include <string>

#include "variable.hxx"


variable::variable(const double min, const double max, const double val)
  : _min(min), _max(max), _val(val)
{
  check_bounds();
}

void variable::set_val(const double val)
{
  if (check_bounds(val)) {
    _val = val;
  }
  return;
}

bool variable::check_bounds(const double val) const
{
  if (val < _min) {
    throw std::out_of_range("Value out of range, " + std::to_string(val)
			    + " < " + std::to_string(_min) + "\n");
  } else if (_max < val) {
    throw std::out_of_range("Value out of range, " + std::to_string(_max)
			    + " < " + std::to_string(val) + "\n");
  }
  return true;
}
