#ifndef __simplefit_function_base__
#define __simplefit_function_base__

#include <memory>
#include <vector>


class function_base {
public:
  virtual operator double () const = 0;
};

// typedefs for convenience
typedef function_base fnbase;
typedef std::shared_ptr<function_base> fnbase_ptr;
typedef std::vector<fnbase_ptr> fnbase_vec;

#endif	// __simplefit_function_base__
