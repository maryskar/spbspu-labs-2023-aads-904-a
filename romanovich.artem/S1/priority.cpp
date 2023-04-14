#include "priority.h"
#include <cstddef>
#include <stdexcept>
size_t romanovich::Priority::getPriority(const std::string &op)
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
bool romanovich::Priority::operator<(const Priority& rhs) const
{
  return priority_ < rhs.priority_;
}
