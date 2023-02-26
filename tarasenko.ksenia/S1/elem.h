#ifndef ELEM_H
#define ELEM_H

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

#endif
