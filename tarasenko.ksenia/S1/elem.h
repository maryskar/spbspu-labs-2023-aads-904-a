#ifndef ELEM_H
#define ELEM_H
#include "math_sym.h"
namespace tarasenko
{
  union Types
  {
    long long operand;
    MathSymbols math_sym;
  };

  class Elem
  {
  public:
   explicit Elem(long long digit);
   explicit Elem(MathSymbols symbols);
   bool isNumber() const;
   long long getOperand() const;
   MathSymbols getOperation() const;
  private:
   Types union_elem_;
   bool is_number_;
  };
}
#endif
