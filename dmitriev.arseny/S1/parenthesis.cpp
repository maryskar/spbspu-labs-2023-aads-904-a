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
{

}
Parenthesis::Parenthesis(Parenthesis&& otherParenthesis) noexcept:
  parenthesis(otherParenthesis.parenthesis)
{

}
char Parenthesis::getCondition()
{
  return 3;
}
long long Parenthesis::getNumber()
{
  throw std::logic_error("logic_error");
}
long long Parenthesis::operator()(long long, long long)
{
  throw std::logic_error("logic_error");
}
bool Parenthesis::isOpenParenthesis()
{
  return isOpen();
}

bool Parenthesis::isCloseParenthesis()
{
  return isClose();
}

char Parenthesis::getPriority()
{
  throw std::logic_error("logic_error");
}

bool Parenthesis::isOpen()
{
  return parenthesis == '(';
}
bool Parenthesis::isClose()
{
  return parenthesis == ')';
}
