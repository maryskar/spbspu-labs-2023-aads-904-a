#ifndef ELEM_H
#define ELEM_H
namespace tarasenko
{
  union Types
  {
    long long int operand;
    char operation;
  };

  struct Elem
  {
    bool is_int;
    Types union_elem;
  };
}
#endif
