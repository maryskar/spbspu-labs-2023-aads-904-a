#ifndef MATHEXPRPTR_H
#define MATHEXPRPTR_H

#include "mathExpression.h"
#include "number.h"
#include "operator.h"
#include "bracket.h"

#include <string>

class ExpressionU
{
public:
  ExpressionU();
  ExpressionU(std::string inp);
  ExpressionU(long long inp);
  ExpressionU(const ExpressionU& otherExprU);
  ExpressionU(ExpressionU&& otherExprU) noexcept;
  ~ExpressionU();

  bool isNumber();
  bool isOperator();
  bool isBracket();

  Number getNumber();
  Operator getOperator();
  Bracket getBracket();

  ExpressionU calculate(ExpressionU e1, ExpressionU e2);

private:
  Expression* eu;
  unsigned* countPtr;

};

#endif
