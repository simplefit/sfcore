#ifndef __simplefit_function__
#define __simplefit_function__

#include <vector>
#include <memory>

#include "function_base.hxx"


class function : public function_base {
public:
  typedef std::vector<fnbase_ptr> fnbase_vec;
  typedef double (* fptr_t) (const fnbase_vec &);

  function(fptr_t fptr, fnbase_vec args)
    : _fptr(fptr), _args(args) {}

  function(fptr_t fptr, unsigned num, fnbase_ptr * args)
    : _fptr(fptr), _args(args, args + num) {}

  ~function() {};

  virtual operator double () const;

  virtual void replace(const unsigned idx, const fnbase_ptr arg);

  fnbase_vec& components();

private:
  fptr_t _fptr;
  fnbase_vec _args;
};

#endif	// __simplefit_function__
