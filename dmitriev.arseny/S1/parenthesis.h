#ifndef PARENTHESIS_H
#define PARENTHESIS_H

#include "mathExpression.h"

class Parenthesis : public Expression
{
public:
  Parenthesis() = default;
  explicit Parenthesis(char parenthesis);
  Parenthesis(const Parenthesis& otherParenthesis);
  Parenthesis(Parenthesis&& otherParenthesis);

  char getCondition() override;
  long long getNumber() override;
  long long getOper(long long, long long) override;
  bool isOpenParenthesis() override;
  bool isCloseParenthesis() override;
  char getPriority() override;

  bool isOpen();
  bool isClose();

private:
  char parenthesis;
};

#endif
