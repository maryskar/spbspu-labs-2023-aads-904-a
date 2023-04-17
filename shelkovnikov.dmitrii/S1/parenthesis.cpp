#include "parenthesis.h"
#include <stdexcept>
dimkashelk::Parenthesis::Parenthesis(char c):
  bracket_(c)
{
  if (!isBracket())
  {
    throw std::logic_error("It's not a bracket");
  }
}
bool dimkashelk::Parenthesis::isOpen() const
{
  return bracket_ == '(';
}
bool dimkashelk::Parenthesis::isClose() const
{
  return bracket_ == ')';
}
bool dimkashelk::Parenthesis::isBracket() const
{
  return isClose() || isOpen();
}
