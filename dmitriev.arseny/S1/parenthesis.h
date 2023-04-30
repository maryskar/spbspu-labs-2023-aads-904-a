#ifndef PARENTHESIS_H
#define PARENTHESIS_H

#include "mathExpression.h"

class Parenthesis : public Expression
{
public:
  explicit Parenthesis(char parenthesis);
  Parenthesis(const Parenthesis& otherParenthesis);
  Parenthesis(Parenthesis&& otherParenthesis) noexcept;

  char getCondition() const override;
  bool isOpenParenthesis() override;
  bool isCloseParenthesis() override;

  bool isOpen();
  bool isClose();

private:
  char parenthesis;

};

#endif
