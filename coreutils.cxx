#include <memory>

#include "coreutils.hxx"
#include "variable.hxx"


fnbase_ptr_vec pod_to_variable(std::vector<double> args)
{
  fnbase_ptr_vec vars(args.size());
  for (unsigned i = 0; i < args.size(); ++i) {
    vars[i] = std::make_shared<variable>(args[i]);
  }
  return vars;
}

fnbase_ptr_vec pod_to_variable(unsigned num, double * args)
{
  std::vector<double> vals(args, args + num);
  return pod_to_variable(vals);
}
