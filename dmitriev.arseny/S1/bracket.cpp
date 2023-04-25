#include "bracket.h"

#include <iomanip>

Bracket::Bracket(char bracket) : //explict
  bracket(bracket)
{
  if (!isOpen() && !isClose())
  {
    throw std::logic_error("this is not end or begining");
  }
}
Bracket::Bracket(const Bracket& otherBracket) :
  bracket(otherBracket.bracket)
{

}
Bracket::Bracket(Bracket&& otherBracket) :
  bracket(otherBracket.bracket)
{

}
char Bracket::getCondition()
{
  return 3;
}
long long Bracket::getNumber()
{
  throw std::logic_error("logic_error");
}
long long Bracket::getOper(long long, long long)
{
  throw std::logic_error("logic_error");
}

bool Bracket::isOpenBracket()
{
  return isOpen();
}

bool Bracket::isCloseBracket()
{
  return isClose();
}

char Bracket::getPriority()
{
  throw std::logic_error("logic_error");
}

bool Bracket::isOpen()
{
  return bracket == '(';
}
bool Bracket::isClose()
{
  return bracket == ')';
}
