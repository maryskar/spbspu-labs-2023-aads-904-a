#ifndef SPBSPU_LABS_2023_AADS_904_A_PART_H
#define SPBSPU_LABS_2023_AADS_904_A_PART_H
#include <string>
namespace dimkashelk
{
  struct PartOfArithmeticExpression
  {
    bool isDigit;
    union element
    {
      long long operand_;
      char operator_;
      explicit element(long long o):
        operand_(o)
      {}
      explicit element(char o):
        operator_(o)
      {}
      explicit element(const std::string &str);
    } element;
    explicit PartOfArithmeticExpression(const std::string &str);
    explicit PartOfArithmeticExpression(long long number);
  };
  bool isGreaterPriority(const PartOfArithmeticExpression &lhs, const PartOfArithmeticExpression &rhs);
}
#endif
