#ifndef __simplefit_boolean__
#define __simplefit_boolean__

#include "function_base.hxx"


class boolean : public function_base {
public:
  boolean(const bool val=true, const bool constant=true);

  boolean(const boolean & other);

  ~boolean() {}

  inline boolean & operator=(const boolean & other) {
    _val = other._val;
    _is_constant = other._is_constant;
    return *this;
  }

  inline virtual operator double () const { return _val; }

  inline operator bool () const { return _val; }

  inline bool is_constant() const { return _is_constant; }

  void set_val(const bool val);

private:
  bool _val;
  bool _is_constant;
};

#endif	// __simplefit_boolean__
