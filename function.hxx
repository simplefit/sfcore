#ifndef __simplefit_function__
#define __simplefit_function__

#include <functional>

#include "function_base.hxx"

#define __fptr_sig__ double (std::vector<double> &)

class function : public function_base {
public:
  typedef std::function<__fptr_sig__> fptr_t;
  // NOTE: Switching to using function objects (either std, or
  // Boost.Function) in comparison to bare function pointers comes
  // with a price; using a generic wrapper means there is no reliable
  // way for the wrapper class to implement a comparison operator.
  //
  // See the two following write-ups for more:
  // - http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2004/n1667.pdf
  // - http://www.boost.org/doc/libs/1_56_0/doc/html/function/faq.html#idp214837184
  //
  // For our purposes, comparing the bare pointers is sufficient.  So
  // we use std::function::target<..>(), see function::operator==(..).
  //
  // Using this allows for easier communication with Python.

  // Default constructor
  function();

  // Construct from a vector of doubles
  function(fptr_t fptr, std::vector<double> & args);

  // Construct from an array of doubles
  function(fptr_t fptr, unsigned num, double * args);

  // Construct from a vector of shared_ptr of variables or functions
  function(fptr_t fptr, fnbase_ptr_vec & args);

  // Construct from an array of variables or functions
  function(fptr_t fptr, unsigned num, fnbase_ptr * args);

  // Construct from a vector of ptrs of variables or functions
  function(fptr_t fptr, std::vector<fnbase*> & args);

  // Construct from an array of ptrs of variables or functions
  function(fptr_t fptr, unsigned num, fnbase * args);

  // Copy constructor
  function(const function & other);

  // Destructor
  virtual ~function();

  // Assignment operator
  virtual function & operator=(const function & other);

  // Comparison operator
  //
  // Compares equality of the underlying function pointer, and vector
  virtual bool operator==(const function & other) const;

  // Inequality operator
  virtual bool operator!=(const function & other) const;

  // Automatic type conversion to double
  virtual operator double () const;

  // Replace the requested function component
  void replace(const unsigned idx, fnbase * arg);

  // Access to underlying function components
  fnbase_ptr_vec& components();

private:
  fptr_t _fptr;			// Underlying function pointer
  fnbase_ptr_vec _args;		// Underlying function components
};

#endif	// __simplefit_function__
