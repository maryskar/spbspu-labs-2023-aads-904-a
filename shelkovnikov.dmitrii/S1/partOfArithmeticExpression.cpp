#include "partOfArithmeticExpression.h"
dimkashelk::PartOfArithmeticExpression::PartOfArithmeticExpression(std::string str)
{
  std::string data("+-*/()%");
  if (str.size() == 1 && data.find(str) != std::string::npos)
  {
    isDigit = false;
    element.operator_ = str[0];
  }
  else
  {
    isDigit = true;
    element.operand_ = std::stoll(str);
  }
}
dimkashelk::PartOfArithmeticExpression::PartOfArithmeticExpression(long long number)
{
  isDigit = true;
  element.operand_ = number;
}
