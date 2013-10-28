#define BOOST_TEST_MODULE test_boolean

#include <stdexcept>
#include <iostream>

#include <boost/test/included/unit_test.hpp>

#include "boolean.hxx"


BOOST_AUTO_TEST_SUITE(test_boolean)

struct boolsetup {
  boolsetup() : mybool(true, false) {}
  ~boolsetup() {}
  boolean mybool;
};

BOOST_FIXTURE_TEST_CASE(automatic_conversion, boolsetup)
{
  BOOST_CHECK(mybool);
}

BOOST_AUTO_TEST_CASE(constant)
{
  boolean constbool(true, true);
  BOOST_CHECK(constbool.is_constant());
  BOOST_REQUIRE_THROW(constbool.set_val(false), std::logic_error);
}

BOOST_FIXTURE_TEST_CASE(setter_access, boolsetup)
{
  mybool.set_val(false);
  BOOST_CHECK(not mybool);
}

BOOST_AUTO_TEST_SUITE_END()
