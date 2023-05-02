#include "parenthesis.h"

#include <stdexcept>

dmitriev::Parenthesis::Parenthesis(char m_parenthesis):
  m_parenthesis(m_parenthesis)
{
  if (!isOpen() && !isClose())
  {
    throw std::logic_error("this is not end or begining");
  }
}
dmitriev::Parenthesis::Parenthesis(const Parenthesis& otherParenthesis):
  m_parenthesis(otherParenthesis.m_parenthesis)
{}
dmitriev::Parenthesis::Parenthesis(Parenthesis&& otherParenthesis) noexcept:
  m_parenthesis(otherParenthesis.m_parenthesis)
{}
char dmitriev::Parenthesis::getCondition() const
{
  return 3;
}

bool dmitriev::Parenthesis::isOpenParenthesis() const
{
  return isOpen();
}

bool dmitriev::Parenthesis::isCloseParenthesis() const
{
  return isClose();
}

bool dmitriev::Parenthesis::isOpen() const
{
  return m_parenthesis == '(';
}
bool dmitriev::Parenthesis::isClose() const
{
  return m_parenthesis == ')';
}
