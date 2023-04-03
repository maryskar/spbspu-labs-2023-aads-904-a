#ifndef SPBSPU_LABS_2023_AADS_904_A_PART_H
#define SPBSPU_LABS_2023_AADS_904_A_PART_H
#include <string>
namespace dimkashelk
{
  struct PartOfArithExpr
  {
    bool isDigit;
    bool isBracket;
    union element
    {
      long long operand_;
      char operator_;
      char bracket_;
      explicit element(long long o):
        operand_(o)
      {}
      explicit element(char o):
        operator_(o)
      {}
      explicit element(const std::string &str);
    } element;
    explicit PartOfArithExpr(const std::string &str);
    explicit PartOfArithExpr(long long number);
    PartOfArithExpr(const PartOfArithExpr &part);
    PartOfArithExpr(PartOfArithExpr &&part);
    PartOfArithExpr &operator=(const PartOfArithExpr &part);
  };
  bool isGreaterPriority(const PartOfArithExpr &lhs, const PartOfArithExpr &rhs);
}
#endif
