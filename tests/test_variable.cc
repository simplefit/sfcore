#define BOOST_TEST_MODULE test_variable

#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

#include "variable.hxx"


struct varsetup {
  varsetup() : myvar(0, 5, 3) {}
  ~varsetup() {}
  variable myvar;
};

BOOST_AUTO_TEST_SUITE(test_variable)

BOOST_FIXTURE_TEST_CASE(automatic_conversion, varsetup)
{
  BOOST_CHECK_EQUAL(3.0, myvar);
}

BOOST_FIXTURE_TEST_CASE(setter_access, varsetup)
{
  myvar.set_val(1);
  BOOST_CHECK_EQUAL(1, myvar);
}

BOOST_FIXTURE_TEST_CASE(assignment_operator, varsetup)
{
  variable myvar2 = myvar;
  BOOST_CHECK_EQUAL(myvar, myvar2);
}

BOOST_FIXTURE_TEST_CASE(value_out_of_range_exception, varsetup)
{
  BOOST_REQUIRE_THROW(myvar.set_val(-1), std::out_of_range);
  // BOOST_REQUIRE_EXCEPTION(myvar.set_val(-1), std::out_of_range,
  // 			  predicate);
}

BOOST_AUTO_TEST_SUITE_END()
