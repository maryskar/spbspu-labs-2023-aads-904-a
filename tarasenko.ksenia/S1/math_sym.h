#ifndef MATH_SYM_H
#define MATH_SYM_H
namespace tarasenko
{
  class MathSymbols
  {
  public:
   MathSymbols(char ms);
   char getValue() const;
   bool operator<(const MathSymbols& rhs) const;
   bool operator>=(const MathSymbols& rhs) const;
  private:
   char value_;
   int priority_;
  };
};
#endif
