#ifndef __simplefit_variable__
#define __simplefit_variable__

#include "function_base.hxx"


class variable : public function_base {
public:
  variable(const double min, const double max, const double val);

  variable(const double val)
    : _min(val), _max(val), _val(val) {}

  variable(const variable & other)
    : _min(other._min), _max(other._max), _val(other._val) {}

  ~variable() {}

  inline variable & operator=(const variable & other) {
    _min = other._min;
    _max = other._max;
    _val = other._val;
    return *this;
  }

  inline virtual operator double () const { return _val; }

  inline bool check_bounds() const { return check_bounds(_val); }

  inline bool is_constant() const {
    return (_min == _max and _min == _val);
  }

  void set_val(const double val);

protected:
  bool check_bounds(const double val) const;

private:
  double _min;
  double _max;
  double _val;
};

#endif	// __simplefit_variable__
