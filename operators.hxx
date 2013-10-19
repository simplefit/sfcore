#ifndef __simplefit_operators__
#define __simplefit_operators__

class fnbase;
class function;

function & operator+(fnbase & lhs, const fnbase & rhs);

function & operator-(fnbase & lhs, const fnbase & rhs);

function & operator*(fnbase & lhs, const fnbase & rhs);

function & operator/(fnbase & lhs, const fnbase & rhs);

function & operator^(fnbase & lhs, const fnbase & rhs);

#endif	// __simplefit_operators__
