#ifndef __simplefit_variable__
#define __simplefit_variable__

#include "function_base.hxx"


class variable : public function_base {
public:
  variable(const double min, const double max, const double val);

  variable(const double val=1);

  variable(const variable & other);

  ~variable() {}

  variable & operator=(const variable & other);

  inline virtual operator double () const { return _val; }

  bool check_bounds() const;

  bool is_constant() const;

  void set_val(const double val);

protected:
  bool check_bounds(const double val) const;

private:
  double _min;
  double _max;
  double _val;
};

#endif	// __simplefit_variable__
