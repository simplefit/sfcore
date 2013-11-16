#define BOOST_TEST_MODULE test_operators

#include <cmath>
#include <stdexcept>

#include <boost/test/included/unit_test.hpp>

#include "coreutils.hxx"
#include "operators.hxx"

#include "testutils.hh"


BOOST_AUTO_TEST_SUITE(test_simple_expressions)

struct fnsetup {
  fnsetup() : myfunc1(nullptr), myfunc2(nullptr)
  {
    double array1[3] = {1, 2, 3};
    myfunc1 = new function(sum, 3, array1);
    double array2[3] = {4, 5, 6};
    myfunc2 = new function(sum, 3, array2);
  }
  ~fnsetup()
  {
    delete myfunc1;
    delete myfunc2;
  }
  function * myfunc1;
  function * myfunc2;
};

BOOST_FIXTURE_TEST_CASE(binary, fnsetup)
{
  function mysum = *myfunc1 + *myfunc2;
  BOOST_CHECK_EQUAL(21.0, mysum); // (1+2+3) + (4+5+6)

  function mydiff_nve = *myfunc1 - *myfunc2;
  BOOST_CHECK_EQUAL(-9.0, mydiff_nve); // (1+2+3) - (4+5+6)
  function mydiff_pve = *myfunc2 - *myfunc1;
  BOOST_CHECK_EQUAL(9.0, mydiff_pve); // (4+5+6) - (1+2+3)

  function myprod = *myfunc1 * *myfunc2;
  BOOST_CHECK_EQUAL(90.0, myprod); // (1+2+3) * (4+5+6)

  function mydiv1 = *myfunc1 / *myfunc2;
  BOOST_CHECK_EQUAL(2.0/5.0, mydiv1); // (1+2+3) / (4+5+6)

  function mydiv2 = *myfunc2 / *myfunc1;
  BOOST_CHECK_EQUAL(5.0/2.0, mydiv2); // (4+5+6) / (1+2+3)

  function zero = *myfunc1 - *myfunc1;
  BOOST_REQUIRE_EQUAL(0.0, zero);
  function nan = *myfunc2 / zero;
  BOOST_CHECK(std::isinf(nan));
}

BOOST_AUTO_TEST_SUITE_END()
