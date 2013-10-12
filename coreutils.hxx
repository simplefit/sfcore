#ifndef __simplefit_coreutils__
#define __simplefit_coreutils__

#include <vector>

#include "function.hxx"


function & make_function(function::fptr_t fptr,
			 std::vector<double> args);

function & make_function(function::fptr_t fptr,
			 unsigned num, double * args);

#endif	// __simplefit_coreutils__
