#include "compare-operations-priority.hpp"

namespace chemodurov
{
  bool isHighPriority(operation_t op)
  {
    return (op == operation_t::DIVIDE || op == operation_t::REMINDER_OF_DIVISION || op == operation_t::MULTIPLICATION);
  }
}

bool chemodurov::isLessPriority(operation_t lhs, operation_t rhs)
{
  return !isHighPriority(lhs) && isHighPriority(rhs);
}
