#include "mathExprPtr.h"

bool isOperator(char inp)
{
  return (inp == '+') || (inp == '-') || (inp == '*') || (inp == '/') || (inp == '%');
}

bool isBracket(char inp)
{
  return (inp == '(') || (inp == ')');
}

Expression* defineMathSymb(std::string inp)
{
  if (isBracket(inp[0]))
  {
    return new Bracket(inp[0]);
  }
  else if (isOperator(inp[0]))
  {
    return new Operator(inp[0]);
  }
  else
  {
    long long i = std::stoll(inp);

    return new Number(i);
  }
}


ExpressionU::ExpressionU():
  eu(nullptr),
  countPtr(new unsigned(0))
{

}

ExpressionU::ExpressionU(std::string inp):
  eu(defineMathSymb(inp)),
  countPtr(new unsigned(1))
{

}

ExpressionU::ExpressionU(long long inp):
  eu(new Number(inp)),
  countPtr(new unsigned(1))
{

}

ExpressionU::ExpressionU(const ExpressionU& otherExprU):
  eu(otherExprU.eu),
  countPtr(otherExprU.countPtr)
{
  (*countPtr)++;
}

ExpressionU::ExpressionU(ExpressionU&& otherExprU) noexcept :
  eu(otherExprU.eu),
  countPtr(otherExprU.countPtr)
{
  otherExprU.eu = nullptr;
  otherExprU.countPtr = nullptr;
}

ExpressionU::~ExpressionU()
{
  if (countPtr && --(*countPtr) == 0)
  {
    delete eu;
    delete countPtr;
  }
}

bool ExpressionU::isNumber()
{
  return eu->isNumber();
}

bool ExpressionU::isOperator()
{
  return eu->isOperator();
}

bool ExpressionU::isBracket()
{
  return eu->isBracket();
}

Number ExpressionU::getNumber()
{
  return *(dynamic_cast<Number*>(eu));
}
Operator ExpressionU::getOperator()
{
  return *(dynamic_cast<Operator*>(eu));
}
Bracket ExpressionU::getBracket()
{
  return *(dynamic_cast<Bracket*>(eu));
}

ExpressionU ExpressionU::calculate(ExpressionU e1, ExpressionU e2)//полное говно
{
  return ExpressionU(getOperator().calculate(e1.getNumber().getLongLong(), e2.getNumber().getLongLong()));
}
