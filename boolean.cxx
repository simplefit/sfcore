#include <stdexcept>

#include "boolean.hxx"


//////////////////
// Constructors //
//////////////////

boolean::boolean(const bool val, const bool constant)
  : _val(val), _is_constant(constant) {}

boolean::boolean(const boolean & other)
  : _val(other._val), _is_constant(other._is_constant) {}

///////////////
// Operators //
///////////////

auto boolean::operator=(const boolean & other) -> boolean &
{
  if (this != &other) {
    _val = other._val;
    _is_constant = other._is_constant;
  }
  return *this;
}

bool boolean::operator==(const boolean & other) const
{
  if (other._val == _val and other._is_constant == _is_constant)
    return true;
  else
    return false;
}

bool boolean::operator!=(const boolean & other) const
{
  return not (*this == other);
}

/////////////
// Methods //
/////////////

void boolean::set_val(const bool val)
{
  if (_is_constant){
    throw std::logic_error("Cannot modify constant `boolean'!");
  }
  _val = val;
}
