#define BOOST_TEST_MODULE test_function

#include <stdexcept>

#include <boost/test/included/unit_test.hpp>

#include "variable.hxx"
#include "coreutils.hxx"


BOOST_AUTO_TEST_SUITE(test_function)

double sum(std::vector<double> & args)
{
  double res(0.);
  for (unsigned i = 0; i < args.size(); ++i) {
    res += double(args[i]);
  }
  return res;
}

struct fnsetup {
  fnsetup() : myfunc(NULL)
  {
    double array[3] = {1, 2, 3};
    myfunc = &make_function(sum, 3, array);
  }
  ~fnsetup()
  {
    delete myfunc;
  }
  function * myfunc;
};

BOOST_FIXTURE_TEST_CASE(automatic_conversion, fnsetup)
{
  BOOST_CHECK_EQUAL(6.0, *myfunc); // 1+2+3
}

BOOST_FIXTURE_TEST_CASE(direct_access, fnsetup)
{
  auto& vars = myfunc->components();
  vars[1] = fnbase_ptr(new variable(3));
  vars[2] = fnbase_ptr(new variable(5));
  BOOST_CHECK_EQUAL(9, *myfunc); // 1+3+5
}

BOOST_FIXTURE_TEST_CASE(setter_access, fnsetup)
{
  for (unsigned i = 0; i < 3; ++i) {
    myfunc->replace(i, new variable((i+1) * 2));
  }
  BOOST_CHECK_EQUAL(12, *myfunc); // 2+4+6
}

BOOST_AUTO_TEST_CASE(functional)
{
  double array[3] = {1, 2, 3};
  auto myfunc1 = fnbase_ptr(&make_function(sum, 3, array)); // 1+2+3
  auto myfunc2 = fnbase_ptr(&make_function(sum, 3, array)); // 1+2+3
  fnbase_vec vars {myfunc1, myfunc2};
  function grandsum(sum, vars); // 6+6
  BOOST_CHECK_EQUAL(12, grandsum);
  function * grandsum_ptr = new function(sum, vars); // 6+6
  BOOST_CHECK_EQUAL(12, *grandsum_ptr);
  delete grandsum_ptr;
}

BOOST_FIXTURE_TEST_CASE(assignment_operator, fnsetup)
{
  function newfn = *myfunc;
  BOOST_CHECK_EQUAL(*myfunc, newfn);
}

BOOST_FIXTURE_TEST_CASE(index_out_of_range_exception, fnsetup)
{
  BOOST_REQUIRE_THROW(myfunc->replace(3, new variable(2)),
		      std::out_of_range);
  // BOOST_REQUIRE_EXCEPTION(myfunc->replace(3, new variable(2)),
  // 			  std::out_of_range, predicate);
}

BOOST_AUTO_TEST_SUITE_END()
