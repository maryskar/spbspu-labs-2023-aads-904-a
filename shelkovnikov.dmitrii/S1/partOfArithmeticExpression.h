#ifndef SPBSPU_LABS_2023_AADS_904_A_PART_H
#define SPBSPU_LABS_2023_AADS_904_A_PART_H
#include <string>
namespace dimkashelk
{
  struct PartOfArithmeticExpression
  {
    explicit PartOfArithmeticExpression(std::string str);
    explicit PartOfArithmeticExpression(long long number);
    bool isDigit;
    union
    {
      long long operand_;
      char operator_;
    } element;
  };
}
#endif
