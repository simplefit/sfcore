#ifndef __simplefit_coreutils__
#define __simplefit_coreutils__

#include "variable.hxx"
#include "function.hxx"


template <typename T>
fnbase_ptr_vec pod_to_variable(std::vector<T> args)
{
  unsigned size(args.size());
  fnbase_ptr_vec vars(size, nullptr);
  for (unsigned i = 0; i < size; ++i) {
    vars[i] = std::make_shared<variable>(args[i]);
  }
  return vars;
}

template <typename T>
fnbase_ptr_vec pod_to_variable(unsigned num, T * args)
{
  std::vector<T> vals(args, args + num);
  return pod_to_variable(vals);
}

#endif	// __simplefit_coreutils__
