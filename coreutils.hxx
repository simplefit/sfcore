#ifndef __simplefit_coreutils__
#define __simplefit_coreutils__

#include <vector>
#include <memory>

#include "variable.hxx"
#include "function.hxx"


template <typename T>
fnbase_ptr_vec pod_to_variable(std::vector<T> args)
{
  fnbase_ptr_vec vars(args.size());
  for (unsigned i = 0; i < args.size(); ++i) {
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
