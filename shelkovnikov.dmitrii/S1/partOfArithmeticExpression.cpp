#include "partOfArithmeticExpression.h"
#include <algorithm>
namespace
{
  bool checkDigit(const std::string &str)
  {
    return str.find_first_not_of("0123456789") == std::string::npos;
  }
}
dimkashelk::PartOfArithmeticExpression::element::element(const std::string &str)
{
  if (checkDigit(str))
  {
    operand_ = std::stoll(str);
  }
  else
  {
    operator_ = str[0];
  }
}
dimkashelk::PartOfArithmeticExpression::PartOfArithmeticExpression(const std::string &str):
  isDigit(checkDigit(str)),
  element(str)
{}
dimkashelk::PartOfArithmeticExpression::PartOfArithmeticExpression(long long number):
  isDigit(true),
  element(number)
{}
