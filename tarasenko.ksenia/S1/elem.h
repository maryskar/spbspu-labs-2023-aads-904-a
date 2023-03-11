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
   Elem(long long digit);
   Elem(MathSymbols symbols);
   bool isDigit() const;
   long long getOperand() const;
   MathSymbols getOperation() const;
  private:
   Types union_elem;
   bool is_int;
  };
}
#endif
