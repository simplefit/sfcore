#include <stdexcept>
#include <string>

#include "function.hxx"


function::operator double () const
{
  std::vector<double> args;
  for (auto itr = _args.begin(); itr != _args.end(); ++itr) {
    args.push_back(**itr);	// itr is pointer to fnbase_ptr
  }
  return _fptr(args);
}

void function::replace(const unsigned idx, fnbase * arg)
{
  if (idx >= _args.size())
    throw std::out_of_range("Index out of range: "
			    + std::to_string(_args.size()) + "(size) >= "
			    + std::to_string(idx) + "(index)");
  _args.at(idx) = fnbase_ptr(arg);
}

auto function::components() -> fnbase_vec &
{
  return _args;
}
