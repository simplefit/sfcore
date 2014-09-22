#define BOOST_TEST_MODULE test_function

#include <stdexcept>

#include <boost/test/included/unit_test.hpp>

#include "coreutils.hxx"

#include "testutils.hh"


BOOST_AUTO_TEST_SUITE(test_function)

struct fnsetup {
  fnsetup() : myfunc(nullptr)
  {
    double array[3] = {1, 2, 3};
    myfunc = new function(sum, 3, array);
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

BOOST_FIXTURE_TEST_CASE(array_access, fnsetup)
{
  BOOST_CHECK_EQUAL(2.0, *(*myfunc)[1]); // fn[1] == 2
  (*myfunc)[1] = std::make_shared<variable>(5);
  BOOST_CHECK_EQUAL(5.0, *(*myfunc)[1]); // fn[1] == 5
  BOOST_CHECK_EQUAL(9.0, *myfunc); // 1+5+3
}

BOOST_FIXTURE_TEST_CASE(direct_access, fnsetup)
{
  auto& vars = myfunc->components();
  vars[1] = std::make_shared<variable>(3);
  vars[2] = std::make_shared<variable>(5);
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
  auto vararray = pod_to_variable(3, array);
  auto myfunc1 = std::make_shared<function>(sum, vararray); // 1+2+3
  auto myfunc2 = std::make_shared<function>(sum, vararray); // 1+2+3
  fnbase_ptr_vec vars {myfunc1, myfunc2};
  function grandsum(sum, vars); // 6+6
  BOOST_CHECK_EQUAL(12, grandsum);
  function * grandsum_ptr = new function(sum, vars); // 6+6
  BOOST_CHECK_EQUAL(12, *grandsum_ptr);
  delete grandsum_ptr;
}

BOOST_FIXTURE_TEST_CASE(index_out_of_range_exception, fnsetup)
{
  BOOST_REQUIRE_THROW(myfunc->replace(3, new variable(2)),
		      std::out_of_range);
  // BOOST_REQUIRE_EXCEPTION(myfunc->replace(3, new variable(2)),
  // 			  std::out_of_range, predicate);
}

BOOST_AUTO_TEST_SUITE_END()
