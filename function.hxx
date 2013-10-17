#ifndef __simplefit_function__
#define __simplefit_function__

#include <memory>

#include "function_base.hxx"


class function : public function_base {
public:
  typedef double (* fptr_t) (std::vector<double> &);

  function(fptr_t fptr, fnbase_vec args)
    : _fptr(fptr), _args(args) {}

  function(fptr_t fptr, unsigned num, fnbase_ptr * args)
    : _fptr(fptr), _args(args, args + num) {}

  function(const function & other)
    : _fptr(other._fptr), _args(other._args) {}

  ~function() {};

  virtual operator double () const;

  void replace(const unsigned idx, fnbase * arg);

  fnbase_vec& components();

private:
  fptr_t _fptr;
  fnbase_vec _args;
};

#endif	// __simplefit_function__
