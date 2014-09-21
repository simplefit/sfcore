#include <stdexcept>
#include <string>

#include "function.hxx"
#include "variable.hxx"


//////////////////
// Constructors //
//////////////////

function::function() : _args(1)
{
  _args[0] = std::make_shared<variable>();
  _fptr = [](std::vector<double> & args) { return args.front(); };
}

function::function(fptr_t fptr, std::vector<double> & args)
  : _fptr(fptr), _args(args.size(), nullptr)
{
  unsigned size(args.size());
  for (unsigned i = 0; i < size; ++i) {
    _args[i] = std::make_shared<variable>(args[i]);
  }
}

function::function(fptr_t fptr, unsigned num, double * args)
  : _fptr(fptr), _args(num, nullptr)
{
  for (unsigned i = 0; i < num; ++i) {
    _args[i] = std::make_shared<variable>(args[i]);
  }
}

function::function(fptr_t fptr, fnbase_ptr_vec & args)
  : _fptr(fptr), _args(args) {}

function::function(fptr_t fptr, unsigned num, fnbase_ptr * args)
  : _fptr(fptr), _args(args, args + num) {}

function::function(fptr_t fptr, std::vector<fnbase*> & args)
  : _fptr(fptr), _args(args.size(), nullptr)
{
  unsigned size(args.size());
  for (unsigned i = 0; i < size; ++i) {
    _args[i] = fnbase_ptr(args[i]);
  }
}

function::function(fptr_t fptr, unsigned num, fnbase * args)
  : _fptr(fptr), _args(num)
{
  for (unsigned i = 0; i < num; ++i) {
    _args[i] = fnbase_ptr(&args[i]);
  }
}

function::function(const function & other)
  : _fptr(other._fptr), _args(other._args) {}

function::~function() {}

///////////////
// Operators //
///////////////

auto function::operator=(const function & other) -> function &
{
  if (this != &other) {
    _fptr = other._fptr;
    _args = other._args;
  }
  return *this;
}

bool function::operator==(const function & other) const
{
  return (other._args == _args and
	  other._fptr.target<__fptr_sig__>() == _fptr.target<__fptr_sig__>());
  // Comparison of functor objects is hard, see header file
}

bool function::operator!=(const function & other) const
{
  return not (*this == other);
}

function::operator double () const
{
  std::vector<double> args;
  args.reserve(_args.size());
  for (auto arg_ptr : _args) {
    args.push_back(*arg_ptr);	// arg_ptr is fnbase_ptr
  }
  return _fptr(args);
}

/////////////
// Methods //
/////////////

void function::replace(const unsigned idx, fnbase * arg)
{
  if (idx >= _args.size())
    throw std::out_of_range("Index out of range: "
			    + std::to_string(_args.size()) + "(size) >= "
			    + std::to_string(idx) + "(index)");
  _args.at(idx) = fnbase_ptr(arg);
}

auto function::components() -> fnbase_ptr_vec &
{
  return _args;
}
