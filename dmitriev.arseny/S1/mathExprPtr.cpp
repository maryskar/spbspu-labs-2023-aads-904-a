#include "mathExprPtr.h"

bool isOperator(char inp);
bool isParenthesis(char inp);
Expression* defineMathSymb(std::string inp);

MathExprPtr::MathExprPtr() :
  adress(nullptr)
{

}

MathExprPtr::MathExprPtr(std::string inp) :
  adress(defineMathSymb(inp))
{

}

MathExprPtr::MathExprPtr(MathExprPtr&& otherMathExprPtr) noexcept://?
  adress(otherMathExprPtr.adress)
{
  otherMathExprPtr.adress = nullptr;
}

Expression* MathExprPtr::getRawPointer() const
{
  return adress;
}

MathExprPtr::~MathExprPtr()
{
  delete adress;
}

Expression* defineMathSymb(std::string inp)
{
  if (isParenthesis(inp[0]))
  {
    return new Parenthesis(inp[0]);
  }
  else if (isOperator(inp[0]))
  {
    return new Operator(inp[0]);
  }
  else
  {
    return new Number(std::stoll(inp));
  }
}

bool isParenthesis(char inp)
{
  return (inp == '(') || (inp == ')');
}

bool isOperator(char inp)
{
  return (inp == '+') || (inp == '-') || (inp == '*') || (inp == '/') || (inp == '%');
}
