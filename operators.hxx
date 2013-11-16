#ifndef __simplefit_operators__
#define __simplefit_operators__

#include "function.hxx"


// FIXME: it should take const references

function & operator+(fnbase & lhs, fnbase & rhs);

function & operator-(fnbase & lhs, fnbase & rhs);

function & operator*(fnbase & lhs, fnbase & rhs);

function & operator/(fnbase & lhs, fnbase & rhs);

// function & operator^(fnbase & lhs, fnbase & rhs);

#endif	// __simplefit_operators__
