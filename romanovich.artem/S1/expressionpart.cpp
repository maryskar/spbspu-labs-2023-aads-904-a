#include "expressionpart.h"
#include <stdexcept>
namespace romanovich
{
  ExpPart::ExpPart(parenthesis_t pr):
    isOperation_(false),
    isParenthesis_(true),
    isOperand_(false),
    content_{pr}
  {
  }
  ExpPart::ExpPart(operations_t op):
    isOperation_(true),
    isParenthesis_(false),
    isOperand_(false),
    content_{op}
  {
  }
  ExpPart::ExpPart(long long op):
    isOperation_(false),
    isParenthesis_(false),
    isOperand_(true),
    content_{op}
  {
  }
  bool ExpPart::isOperation() const
  {
    return isOperation_;
  }
  bool ExpPart::isParenthesis() const
  {
    return isParenthesis_;
  }
  bool ExpPart::isOperand() const
  {
    return isOperand_;
  }
  operations_t ExpPart::getOperation() const
  {
    if (isOperation_)
    {
      return content_.operation_;
    }
    throw std::logic_error("Not operation.");
  }
  long long ExpPart::getOperand() const
  {
    if (isOperand_)
    {
      return content_.operand_;
    }
    throw std::logic_error("Not operand.");
  }
  parenthesis_t ExpPart::getParenthesis() const
  {
    if (isParenthesis_)
    {
      return content_.parenthesis_;
    }
    throw std::logic_error("Not parenthesis.");
  }
  ExpPart::ExpContent::ExpContent(parenthesis_t pr):
    parenthesis_(pr)
  {
  }
  ExpPart::ExpContent::ExpContent(operations_t op):
    operation_(op)
  {
  }
  ExpPart::ExpContent::ExpContent(long long op):
    operand_(op)
  {
  }
}
romanovich::ExpPart romanovich::createFromString(const std::string &string)
{
  const char sym = string[0];
  if (sym == as_char(romanovich::parenthesis_t::right))
  {
    return romanovich::ExpPart(romanovich::parenthesis_t::right);
  }
  if (sym == as_char(romanovich::parenthesis_t::left))
  {
    return romanovich::ExpPart(romanovich::parenthesis_t::left);
  }
  if (sym == as_char(romanovich::operations_t::division))
  {
    return romanovich::ExpPart(romanovich::operations_t::division);
  }
  if (sym == as_char(romanovich::operations_t::multiplication))
  {
    return romanovich::ExpPart(romanovich::operations_t::multiplication);
  }
  if (sym == as_char(romanovich::operations_t::minus))
  {
    return romanovich::ExpPart(romanovich::operations_t::minus);
  }
  if (sym == as_char(romanovich::operations_t::plus))
  {
    return romanovich::ExpPart(romanovich::operations_t::plus);
  }
  if (sym == as_char(romanovich::operations_t::division_remainder))
  {
    return romanovich::ExpPart(romanovich::operations_t::division_remainder);
  }
  try
  {
    long long operand = std::stoll(string, nullptr, 10);
    return romanovich::ExpPart(operand);
  }
  catch (...)
  {
    throw std::logic_error("Cannot make expression part.");
  }
}
