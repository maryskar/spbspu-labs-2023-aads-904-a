#ifndef ELEM_H
#define ELEM_H
namespace tarasenko
{
  struct Elem
  {
  public:
   Elem(long long digit);
   Elem(char op);
   bool isDigit() const;
   long long getValueOfOperand() const;
   char getValueOfOperation() const;
  private:
   union Types
   {
     long long int operand;
     char operation; // OPERATION operation
   };
   Types union_elem;
   bool is_int;
  };
}
#endif
