#include <stdexcept>

#include "boolean.hxx"


//////////////////
// Constructors //
//////////////////

boolean::boolean(const bool val, const bool constant)
  : _val(val), _is_constant(constant) {}

boolean::boolean(const boolean & other)
  : _val(other._val), _is_constant(other._is_constant) {}

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
