#define BOOST_TEST_MODULE test_experimental

#include <stdexcept>
#include <memory>

#include <boost/test/included/unit_test.hpp>

#include "variable.hxx"
#include "function.hxx"


BOOST_AUTO_TEST_SUITE(test_experimental)

double sum(std::vector<double> & args)
{
  double res(0.);
  for (unsigned i = 0; i < args.size(); ++i) {
    res += double(args[i]);
  }
  return res;
}

struct compsetup {
  compsetup() : myfuncvar(NULL), myvar(NULL), varsum(NULL)
  {
    myfuncvar = std::make_shared<function>(); // 1
    myvar = std::make_shared<variable>();     // 1
    fnbase_vec vars {myfuncvar, myvar};
    varsum = std::make_shared<function>(sum, vars); // 1+1
  }
  ~compsetup() {}
  fnbase_ptr myfuncvar;
  fnbase_ptr myvar;
  fnbase_ptr varsum;
};

BOOST_FIXTURE_TEST_CASE(compare_variable_impl, compsetup)
{
  BOOST_CHECK_EQUAL(2, *varsum);
}

BOOST_AUTO_TEST_SUITE_END()
