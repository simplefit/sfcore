#ifndef __simplefit_function__
#define __simplefit_function__

#include "function_base.hxx"


class function : public function_base {
public:
  typedef double (* fptr_t) (std::vector<double> &);

  function();

  function(fptr_t fptr, std::vector<double> args);

  function(fptr_t fptr, unsigned num, double * args);

  function(fptr_t fptr, fnbase_ptr_vec & args);

  function(fptr_t fptr, unsigned num, fnbase_ptr * args);

  function(fptr_t fptr, std::vector<fnbase*> & args);

  function(fptr_t fptr, unsigned num, fnbase * args);

  function(const function & other);

  virtual ~function();

  function & operator=(const function & other);

  virtual operator double () const;

  void replace(const unsigned idx, fnbase * arg);

  fnbase_ptr_vec& components();

private:
  fptr_t _fptr;
  fnbase_ptr_vec _args;
};

#endif	// __simplefit_function__
