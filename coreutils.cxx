#include "coreutils.hxx"
#include "variable.hxx"


function & make_function(function::fptr_t fptr,
			   std::vector<double> args)
{
  fnbase_vec vars(args.size());
  for (unsigned i = 0; i < args.size(); ++i) {
    vars[i] = fnbase_ptr(new variable(args[i]));
  }
  function * fn = new function(fptr, vars);
  return *fn;
}

function & make_function(function::fptr_t fptr,
			 unsigned num, double * args)
{
  std::vector<double> vals(args, args + num);
  return make_function(fptr, vals);
}
