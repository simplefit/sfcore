#include <cassert>

#include "operators.hxx"


function & operator-(fnbase & rhs)
{
  function::fptr_t neg_fptr = [](std::vector<double> & args) {
    return -args.front();
  };
  return *(new function(neg_fptr, 1, &rhs));
}

function & operator+=(fnbase & lhs, /* const */ fnbase & rhs)
{
  fnbase_ptr_vec sum_args = {fnbase_ptr(&lhs), fnbase_ptr(&rhs)};
  function::fptr_t sum_fptr = [](std::vector<double> & args) {
    assert(2 == args.size());
    return args[0] + args[1];
  };
  return *(new function(sum_fptr, sum_args));
}

function & operator+(fnbase & lhs, /* const */ fnbase & rhs)
{
  return lhs += rhs;
}

function & operator-=(fnbase & lhs, /* const */ fnbase & rhs)
{
  fnbase_ptr_vec diff_args = {fnbase_ptr(&lhs), fnbase_ptr(&rhs)};
  function::fptr_t diff_fptr = [](std::vector<double> & args) {
    assert(2 == args.size());
    return args[0] - args[1];
  };
  return *(new function(diff_fptr, diff_args));
}

function & operator-(fnbase & lhs, /* const */ fnbase & rhs)
{
  return lhs -= rhs;
}

function & operator*=(fnbase & lhs, fnbase & rhs)
{
  fnbase_ptr_vec prod_args = {fnbase_ptr(&lhs), fnbase_ptr(&rhs)};
  function::fptr_t prod_fptr = [](std::vector<double> & args) {
    assert(2 == args.size());
    return args[0] * args[1];
  };
  return *(new function(prod_fptr, prod_args));
}

function & operator*(fnbase & lhs, /* const */ fnbase & rhs)
{
  return lhs *= rhs;
}

function & operator/=(fnbase & lhs, /* const */ fnbase & rhs)
{
  fnbase_ptr_vec div_args = {fnbase_ptr(&lhs), fnbase_ptr(&rhs)};
  function::fptr_t div_fptr = [](std::vector<double> & args) {
    assert(2 == args.size());
    // assert(args[1] != 0);
    return args[0] / args[1];	// pass on inf, do not want to crash
  };
  return *(new function(div_fptr, div_args));
}

function & operator/(fnbase & lhs, /* const */ fnbase & rhs)
{
  return lhs /= rhs;
}
