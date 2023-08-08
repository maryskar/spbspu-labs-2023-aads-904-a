#ifndef SPBSPU_LABS_2023_AADS_904_A_PART_H
#define SPBSPU_LABS_2023_AADS_904_A_PART_H
#include <string>
#include "parenthesis.h"
#include "operator.h"
namespace dimkashelk
{
  class PartOfArithExpr
  {
  public:
    explicit PartOfArithExpr(Parenthesis parenthesis);
    explicit PartOfArithExpr(Operator oper);
    explicit PartOfArithExpr(long long number);
    PartOfArithExpr(const PartOfArithExpr &part);
    PartOfArithExpr(PartOfArithExpr &&part);
    PartOfArithExpr &operator=(const PartOfArithExpr &part);
    PartOfArithExpr &operator=(PartOfArithExpr &&part);
    bool isNumber() const;
    bool isParenthesis() const;
    Operator getOperator() const;
    Parenthesis getParenthesis() const;
    long long getOperand() const;
  private:
    bool isNumber_;
    bool isParenthesis_;
    union element
    {
      long long operand_;
      Operator operator_;
      Parenthesis parenthesis_;
      explicit element(long long o);
      explicit element(Operator oper);
      explicit element(Parenthesis parenthesis);
    } element;
  };
  bool isGreaterPriority(const Operator &lhs, const Operator &rhs);
}
#endif
