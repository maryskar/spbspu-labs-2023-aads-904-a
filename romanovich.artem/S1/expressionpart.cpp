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
  ExpPart::ExpContent::ExpContent(parenthesis_t pr): parenthesis_(pr)
  {
  }
  ExpPart::ExpContent::ExpContent(operations_t op): operation_(op)
  {
  }
  ExpPart::ExpContent::ExpContent(long long op): operand_(op)
  {
  }
}
