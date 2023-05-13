#include "mathExprPtr.h"

namespace
{
  bool isParenthesis(char inp)
  {
    return (inp == '(') || (inp == ')');
  }

  //bool isEnd(char inp)
  //{
  //  return (inp == '\0');
  //}

  bool isOperator(char inp)
  {
    return (inp == '+') || (inp == '-') || (inp == '*') || (inp == '/') || (inp == '%');
  }

  dmitriev::Expression* defineMathSymb(std::string inp)
  {
    if (isParenthesis(inp[0]) && (inp.size() == 1))
    {
      return new dmitriev::Parenthesis(inp[0]);
    }
    else if (isOperator(inp[0]) && (inp.size() == 1))
    {
      return new dmitriev::Operator(inp[0]);
    }
    else
    {
      return new dmitriev::Number(std::stoll(inp));
    }
  }
}

dmitriev::MathExprPtr::MathExprPtr():
  m_adress(nullptr)
{}

dmitriev::MathExprPtr::MathExprPtr(std::string inp):
  m_adress(defineMathSymb(inp))
{}

dmitriev::MathExprPtr::MathExprPtr(MathExprPtr&& otherMathExprPtr) noexcept:
  m_adress(otherMathExprPtr.m_adress)
{
  otherMathExprPtr.m_adress = nullptr;
}

dmitriev::MathExprPtr& dmitriev::MathExprPtr::operator=(MathExprPtr&& otherMathExprPtr) noexcept
{
  m_adress = otherMathExprPtr.m_adress;
  otherMathExprPtr.m_adress = nullptr;

  return *this;
}

dmitriev::Expression* dmitriev::MathExprPtr::operator*()
{
  return m_adress;
}

dmitriev::Expression* dmitriev::MathExprPtr::operator->()
{
  return m_adress;
}

dmitriev::MathExprPtr::~MathExprPtr()
{
  delete m_adress;
}
