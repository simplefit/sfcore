#ifndef __simplefit_coreutils__
#define __simplefit_coreutils__

#include <vector>

#include "function.hxx"


fnbase_ptr_vec pod_to_variable(std::vector<double> args);

fnbase_ptr_vec pod_to_variable(unsigned num, double * args);

#endif	// __simplefit_coreutils__
