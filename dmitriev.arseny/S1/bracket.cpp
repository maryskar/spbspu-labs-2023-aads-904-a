#include "bracket.h"

#include <iomanip>

Bracket::Bracket(char bracket):
  bracket(bracket)
{
  if (!isOpen() && !isClose())
  {
    throw std::logic_error("this is not end or begining");
  }
}
Bracket::Bracket(const Bracket& otherBracket):
  bracket(otherBracket.bracket)
{

}
Bracket::Bracket(Bracket&& otherBracket):
  bracket(otherBracket.bracket)
{

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
