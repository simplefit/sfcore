#ifndef __simplefit_boolean__
#define __simplefit_boolean__

#include "function_base.hxx"


class boolean : public function_base {
public:
  // Default constructor
  boolean(const bool val=true, const bool constant=true);

  // Copy constructor
  boolean(const boolean & other);

  // Destructor
  ~boolean() {}

  // Assignment operator
  virtual boolean & operator=(const boolean & other);

  // Comparison operator
  virtual bool operator==(const boolean & other) const;

  // Inequality operator
  virtual bool operator!=(const boolean & other) const;

  // Automatic type conversion to double
  inline virtual operator double () const { return _val; }

  // Automatic type conversion to boolean
  inline operator bool () const { return _val; }

  // Ask if constant
  inline bool is_constant() const { return _is_constant; }

  // Setter
  void set_val(const bool val);

private:
  bool _val;			// Value
  bool _is_constant;		// Constant flag
};

#endif	// __simplefit_boolean__
