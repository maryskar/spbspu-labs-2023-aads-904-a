#include <cstddef>
#include <iostream>
#include "priority.h"
size_t Priority::getPriority(const std::string &op)
{
  if (op == "+" || op == "-")
  {
    return 1;
  }
  if (op == "*" || op == "/" || op == "%")
  {
    return 2;
  }
  throw std::invalid_argument("Priority parse error");
}
bool Priority::operator>=(const Priority& rhs) const
{
  return priority_ >= rhs.priority_;
}
