#include "priority.h"
#include <cstddef>
#include <stdexcept>
size_t romanovich::Priority::getPriority(const operations_t &op)
{
  if (op == operations_t::plus || op == operations_t::minus)
  {
    return 1;
  }
  if (op == operations_t::multiplication || op == operations_t::division || op == operations_t::division_remainder)
  {
    return 2;
  }
  throw std::invalid_argument("Priority parse error");
}
bool romanovich::Priority::operator<(const Priority &rhs) const
{
  return priority_ < rhs.priority_;
}
romanovich::Priority::Priority(operations_t op):
  priority_(Priority::getPriority(op))
{}