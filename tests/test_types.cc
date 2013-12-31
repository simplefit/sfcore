#define BOOST_TEST_MODULE test_types

#include <type_traits>

#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include "variable.hxx"
#include "boolean.hxx"
#include "function.hxx"


typedef boost::mpl::list<variable,boolean,function> types;

BOOST_AUTO_TEST_SUITE(test_types)

BOOST_AUTO_TEST_CASE_TEMPLATE(default_constructible, T, types)
{
  BOOST_CHECK(std::is_default_constructible<T>::value);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(copy_constructible, T, types)
{
  BOOST_CHECK(std::is_copy_constructible<T>::value);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(move_constructible, T, types)
{
  BOOST_CHECK(std::is_move_constructible<T>::value);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(destructible, T, types)
{
  BOOST_CHECK(std::is_destructible<T>::value);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(has_virtual_destructor, T, types)
{
  BOOST_CHECK(std::has_virtual_destructor<T>::value);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(assignable, T, types)
{
  // copy assignable: operator=(const Type& other)
  BOOST_CHECK(std::is_copy_assignable<T>::value);
  // above implies move assignable (don't understand exactly)
  BOOST_CHECK(std::is_move_assignable<T>::value);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(comparison, T, types)
{
  T myinstance;
  // since != implemented using ==, need to check only one
  // FIXME: Why the following doesn't compile?
  // BOOST_CHECK_EQUAL(myinstance, myinstance);
  BOOST_CHECK(myinstance == myinstance);
}

BOOST_AUTO_TEST_SUITE_END()
