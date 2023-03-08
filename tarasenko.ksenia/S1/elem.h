#ifndef ELEM_H
#define ELEM_H
#include "type_operation.h"
namespace tarasenko
{
  union Types
  {
    long long operand;
    Operation operation;
  };

  class Elem
  {
  public:
   Elem(long long digit);
   Elem(Operation op);
   bool isDigit() const;
   long long getOperand() const;
   Operation getOperation() const;
  private:
   Types union_elem;
   bool is_int;
  };
}
#endif
