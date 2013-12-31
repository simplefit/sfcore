#include <stdexcept>
#include <string>

#include <boost/format.hpp>

#include "variable.hxx"


//////////////////
// Constructors //
//////////////////

variable::variable(const double min, const double max, const double val)
  : _min(min), _max(max), _val(val)
{
  check_bounds();
}

variable::variable(const double val)
  : _min(val), _max(val), _val(val) {}

variable::variable(const variable & other)
  : _min(other._min), _max(other._max), _val(other._val) {}

///////////////
// Operators //
///////////////

auto variable::operator=(const variable & other) -> variable &
{
  if (this != &other) {
    _min = other._min;
    _max = other._max;
    _val = other._val;
  }
  return *this;
}

bool variable::operator==(const variable & other) const
{
  if (other._min == _min and
      other._max == _max and
      other._val == _val)
    return true;
  else
    return false;
}

bool variable::operator!=(const variable & other) const
{
  return not (*this == other);
}

/////////////
// Methods //
/////////////

bool variable::check_bounds() const
{
 return check_bounds(_val);
}

bool variable::is_constant() const
{
  return (_min == _max and _min == _val);
}

void variable::set_val(const double val)
{
  if (is_constant()) {
    throw std::logic_error("Cannot modify constant `variable'!");
  }
  if (check_bounds(val)) {
    _val = val;
  }
  return;
}

bool variable::check_bounds(const double val) const
{
  boost::format msg("Value out of range, %s < %s\n");
  if (val < _min) {
    throw std::out_of_range(boost::str(msg % val % _min));
  } else if (_max < val) {
    throw std::out_of_range(boost::str(msg % _max % val));
  }
  return true;
}
