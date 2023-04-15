#include "bracket.h"

#include <iomanip>

Bracket::Bracket(char bracket): //explict
  bracket(bracket)
{
  if (!isOpen() && !isClose())
  {
    throw std::logic_error("this is not end or begining");
  }
}
char Bracket::getCondition()
{
  return 3;
}
bool Bracket::isOpen()
{
  return bracket == '(';
}
bool Bracket::isClose()
{
  return bracket == ')';
}
