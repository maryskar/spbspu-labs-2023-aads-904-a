#include "operator.h"
#include <stdexcept>
dimkashelk::Operator::Operator(const std::string &str):
  operator_(str)
{
  if (!isOperator())
  {
    throw std::logic_error("It's not a operator");
  }
}
dimkashelk::Operator::~Operator()
{}
bool dimkashelk::Operator::isAdd()
{
  return operator_ == "+";
}
bool dimkashelk::Operator::isSubtraction()
{
  return operator_ == "-";
}
bool dimkashelk::Operator::isMultiplication()
{
  return operator_ == "*";
}
bool dimkashelk::Operator::isDivision()
{
  return operator_ == "/";
}
bool dimkashelk::Operator::isRemainder()
{
  return operator_ == "%";
}
bool dimkashelk::Operator::isOperator()
{
  return operator_.find_first_not_of("+-/*%") != std::string::npos;
}
