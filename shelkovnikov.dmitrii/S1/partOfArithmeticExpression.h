#ifndef SPBSPU_LABS_2023_AADS_904_A_PART_H
#define SPBSPU_LABS_2023_AADS_904_A_PART_H
#include <string>
#include "parenthesis.h"
namespace dimkashelk
{
  class PartOfArithExpr
  {
  public:
    explicit PartOfArithExpr(const std::string &str);
    explicit PartOfArithExpr(long long number);
    PartOfArithExpr(const PartOfArithExpr &part);
    PartOfArithExpr(PartOfArithExpr &&part);
    PartOfArithExpr &operator=(const PartOfArithExpr &part);
    PartOfArithExpr &operator=(PartOfArithExpr &&part);
    bool isDigit() const;
    bool isBracket() const;
    char getOperator() const;
    Parenthesis getBracket() const;
    long long getOperand() const;
  private:
    bool isDigit_;
    bool isBracket_;
    union element
    {
      long long operand_;
      char operator_;
      Parenthesis bracket_;
      explicit element(long long o);
      explicit element(char o);
      explicit element(const std::string &str);
    } element;
  };
  bool isGreaterPriority(const PartOfArithExpr &lhs, const PartOfArithExpr &rhs);
}
#endif
