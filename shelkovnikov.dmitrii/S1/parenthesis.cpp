#include "parenthesis.h"
#include <stdexcept>
dimkashelk::Parenthesis::Parenthesis(char c):
  parenthesis_(c)
{
  if (!isParenthesis())
  {
    throw std::logic_error("It's not a bracket");
  }
}
bool dimkashelk::Parenthesis::isOpen() const
{
  return parenthesis_ == '(';
}
bool dimkashelk::Parenthesis::isClose() const
{
  return parenthesis_ == ')';
}
bool dimkashelk::Parenthesis::isParenthesis() const
{
  return isClose() || isOpen();
}
