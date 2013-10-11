#ifndef __simplefit_function_base__
#define __simplefit_function_base__

#include <memory>


class function_base {
public:
  typedef std::shared_ptr<function_base> fnbase_ptr;

  virtual operator double () const = 0;

  virtual void replace(const unsigned idx, const fnbase_ptr arg) = 0;
};

#endif	// __simplefit_function_base__
