#ifndef __simplefit_function__
#define __simplefit_function__

#include <utility>


class function {
public:
  function(unsigned num, double * args, double (* fptr) (unsigned, double *))
    : _num(num), _args(args), _fptr(fptr) {}
  ~function() {};

  operator double () const;

  void set_param(unsigned idx, double val);
  std::pair<int, double *> params() const;

private:
  unsigned _num;
  double * _args;
  double (* _fptr) (unsigned, double *);
};

#endif	// __simplefit_function__
