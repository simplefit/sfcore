#ifndef __simplefit_variable__
#define __simplefit_variable__

#include "function_base.hxx"


class variable : public function_base {
public:
  // Default constructor
  variable(const double val=1);

  // Construct from double with a range
  variable(const double min, const double max, const double val);

  // Copy constructor
  variable(const variable & other);

  // Destructor
  ~variable() {}

  // Assignment operator
  virtual variable & operator=(const variable & other);

  // Comparison operator
  virtual bool operator==(const variable & other) const;

  // Inequality operator
  virtual bool operator!=(const variable & other) const;

  // Automatic type conversion to double
  inline virtual operator double () const { return _val; }

  // Check bounds, throws std::out_of_range on fail
  bool check_bounds() const;

  // If variable is a constant, true when range max == min
  bool is_constant() const;

  // Set value, throws std::out_of_range when out of range
  void set_val(const double val);

protected:
  bool check_bounds(const double val) const;

private:
  double _min;			// Range minimum
  double _max;			// Range maximum
  double _val;			// Numeric value
};

#endif	// __simplefit_variable__
