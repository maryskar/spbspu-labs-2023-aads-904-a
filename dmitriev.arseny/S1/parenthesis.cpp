#include "parenthesis.h"

#include <iomanip>

Parenthesis::Parenthesis(char parenthesis):
  parenthesis(parenthesis)
{
  if (!isOpen() && !isClose())
  {
    throw std::logic_error("this is not end or begining");
  }
}
Parenthesis::Parenthesis(const Parenthesis& otherParenthesis):
  parenthesis(otherParenthesis.parenthesis)
{}
Parenthesis::Parenthesis(Parenthesis&& otherParenthesis) noexcept:
  parenthesis(otherParenthesis.parenthesis)
{}
char Parenthesis::getCondition()
{
  return 3;
}

bool Parenthesis::isOpenParenthesis()
{
  return isOpen();
}

bool Parenthesis::isCloseParenthesis()
{
  return isClose();
}

bool Parenthesis::isOpen()
{
  return parenthesis == '(';
}
bool Parenthesis::isClose()
{
  return parenthesis == ')';
}
