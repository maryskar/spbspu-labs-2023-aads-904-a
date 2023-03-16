#include <cstddef>
#include <iostream>
#include "operation.h"
size_t Operation::getPriority(const std::string &op)
{
  if (op == "+" || op == "-")
  {
    return 1;
  }
  if (op == "*" || op == "/" || op == "%")
  {
    return 2;
  }
  throw std::invalid_argument("Operation parse error");
}
bool Operation::operator<=(const Operation& rhs) const
{
  return priority_ <= rhs.priority_;
}
