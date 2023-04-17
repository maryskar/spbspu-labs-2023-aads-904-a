#include "bracket.h"
#include <stdexcept>
dimkashelk::Bracket::Bracket(char c):
  bracket_(c)
{
  if (!isBracket())
  {
    throw std::logic_error("It's not a bracket");
  }
}
bool dimkashelk::Bracket::isOpen() const
{
  return bracket_ == '(';
}
bool dimkashelk::Bracket::isClose() const
{
  return bracket_ == ')';
}
bool dimkashelk::Bracket::isBracket() const
{
  return isClose() || isOpen();
}
