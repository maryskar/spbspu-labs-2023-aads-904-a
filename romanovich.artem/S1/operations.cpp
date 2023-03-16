#include <cstddef>
#include "operations.h"
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
  return 0;
}
bool Operation::isGreaterPriority(const Operation &lhs, const Operation &rhs)
{
  return getPriority(lhs.operation_) > getPriority(rhs.operation_);
}
bool Operation::operator<=(const Operation& rhs) const
{
  return priority_ <= rhs.priority_;
}