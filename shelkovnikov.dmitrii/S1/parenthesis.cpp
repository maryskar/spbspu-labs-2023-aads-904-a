#include "parenthesis.h"
#include <stdexcept>
dimkashelk::Parenthesis::Parenthesis(char c):
  parenthesis_(c)
{
  if (!isParenthesis(c))
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
bool dimkashelk::Parenthesis::isParenthesis(char c)
{
  return c == '(' || c == ')';
}
