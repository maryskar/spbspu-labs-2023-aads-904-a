#include "operator.h"
#include <stdexcept>
dimkashelk::Operator::Operator(std::string &str):
  operator_(str)
{
  if (!isOperator())
  {
    throw std::logic_error("It's not a operator");
  }
}
bool dimkashelk::Operator::isOperator()
{
  return operator_.find_first_not_of("+-/*%") != std::string::npos;
}
