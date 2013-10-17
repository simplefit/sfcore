#define BOOST_TEST_MODULE test_function

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

#include "function.hxx"
#include "variable.hxx"
#include "coreutils.hxx"


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
  ~fnsetup() {}
  function * myfunc;
};

BOOST_AUTO_TEST_SUITE(test)

BOOST_FIXTURE_TEST_CASE(automatic_conversion, fnsetup)
{
  BOOST_CHECK_EQUAL(6.0, *myfunc);
}

BOOST_FIXTURE_TEST_CASE(direct_access, fnsetup)
{
  auto& vars = myfunc->components();
  vars[1] = fnbase_ptr(new variable(3));
  vars[2] = fnbase_ptr(new variable(5));
  BOOST_CHECK_EQUAL(9, *myfunc);
}

BOOST_FIXTURE_TEST_CASE(setter_access, fnsetup)
{
  for (unsigned i = 0; i < 3; ++i) {
    myfunc->replace(i, new variable((i+1) * 2));
  }
  BOOST_CHECK_EQUAL(12, *myfunc);
}

BOOST_FIXTURE_TEST_CASE(index_out_of_range_exception, fnsetup)
{
  BOOST_REQUIRE_THROW(myfunc->replace(3, new variable(2)),
		      std::out_of_range);
  // BOOST_REQUIRE_EXCEPTION(myfunc->replace(3, new variable(2)),
  // 			  std::out_of_range, predicate);
}

BOOST_AUTO_TEST_SUITE_END()
