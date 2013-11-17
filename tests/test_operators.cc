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

struct poly_fnsetup {
  poly_fnsetup() : myvar(nullptr), myfunc(nullptr)
  {
    myvar = new variable(0, 10, 7);
    double array[3] = {1, 2, 3};
    myfunc = new function(sum, 3, array);
  }
  ~poly_fnsetup()
  {
    delete myvar;
    delete myfunc;
  }
  variable * myvar;
  function * myfunc;
};

BOOST_FIXTURE_TEST_CASE(unary, poly_fnsetup)
{
  function newfunc1 = -*myvar;
  BOOST_CHECK_EQUAL(-7.0, newfunc1); // -7

  function newfunc2 = -*myfunc;
  BOOST_CHECK_EQUAL(-6.0, newfunc2); // -7
}

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
  BOOST_CHECK_EQUAL(0.0, zero);
  function inf = *myfunc2 / zero;
  BOOST_CHECK(std::isinf(inf));	// (4+5+6) / 0
}

BOOST_FIXTURE_TEST_CASE(polymorphic_binary, poly_fnsetup)
{
  function mysum = *myvar + *myfunc;
  BOOST_CHECK_EQUAL(13.0, mysum); // 7 + (1+2+3)

  function mydiff_pve = *myvar - *myfunc;
  BOOST_CHECK_EQUAL(1.0, mydiff_pve); // 7 - (1+2+3)
  function mydiff_nve = *myfunc - *myvar;
  BOOST_CHECK_EQUAL(-1.0, mydiff_nve); // (1+2+3) - 7

  function myprod = *myvar * *myfunc;
  BOOST_CHECK_EQUAL(42.0, myprod); // 7 * (1+2+3)

  function mydiv1 = *myvar / *myfunc;
  BOOST_CHECK_EQUAL(7.0/6.0, mydiv1); // 7 / (1+2+3)

  function mydiv2 = *myfunc / *myvar;
  BOOST_CHECK_EQUAL(6.0/7.0, mydiv2); // (1+2+3) / 7

  variable unity(1.0);
  function inv =  unity / *myvar;
  BOOST_CHECK_EQUAL(1.0/7.0, inv); // 1 / 7

  function zero = *myfunc - *myfunc;
  BOOST_CHECK_EQUAL(0.0, zero);
  function inf = *myvar / zero;
  BOOST_CHECK(std::isinf(inf));	// (1+2+3) / 0
}

BOOST_FIXTURE_TEST_CASE(ownership, poly_fnsetup)
{
  function grandsum = *myfunc + *myfunc;
  BOOST_CHECK_EQUAL(12.0, grandsum); // (1+2+3) + (1+2+3)

  // retrieve pointers
  auto & comp_ptr_vec = grandsum.components();
  // since same function, pointers are equal
  BOOST_CHECK_EQUAL(comp_ptr_vec[0].get(), comp_ptr_vec[1].get());
  function & sum1 = dynamic_cast<function&>(*comp_ptr_vec[0]);
  function & sum2 = dynamic_cast<function&>(*comp_ptr_vec[1]);

  // replace variables
  auto & comp_ptr_vec_1 = sum1.components();
  comp_ptr_vec_1[0] = std::make_shared<variable>(6); // 1 -> 6
  BOOST_CHECK_EQUAL(22.0, grandsum); // (6+2+3) + (6+2+3)
  auto & comp_ptr_vec_2 = sum2.components();
  comp_ptr_vec_2[1] = std::make_shared<variable>(6); // 2 -> 6
  BOOST_CHECK_EQUAL(30.0, grandsum); // (6+6+3) + (6+6+3)
}

BOOST_AUTO_TEST_SUITE_END()
