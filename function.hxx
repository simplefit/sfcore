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

  function();

  function(fptr_t fptr, std::vector<double> & args);

  function(fptr_t fptr, unsigned num, double * args);

  function(fptr_t fptr, fnbase_ptr_vec & args);

  function(fptr_t fptr, unsigned num, fnbase_ptr * args);

  function(fptr_t fptr, std::vector<fnbase*> & args);

  function(fptr_t fptr, unsigned num, fnbase * args);

  function(const function & other);

  virtual ~function();

  virtual function & operator=(const function & other);

  virtual bool operator==(const function & other) const;

  virtual bool operator!=(const function & other) const;

  virtual operator double () const;

  void replace(const unsigned idx, fnbase * arg);

  fnbase_ptr_vec& components();

private:
  fptr_t _fptr;
  fnbase_ptr_vec _args;
};

#endif	// __simplefit_function__
