#include "compare-operations-priority.hpp"

int chemodurov::compareOperationsPriority(Operation lhs, Operation rhs)
{
  int lhs_prior = 0;
  int rhs_prior = 0;
  if (lhs == OPERATION_MINUS || lhs == OPERATION_PLUS)
  {
    lhs_prior = 0;
  }
  else if (lhs == OPERATION_DIVIDE || lhs == OPERATION_REMINDER_OF_DIVISION || lhs == OPERATION_MULTIPLICATION)
  {
    lhs_prior = 1;
  }
  if (rhs == OPERATION_MINUS || rhs == OPERATION_PLUS)
  {
    rhs_prior = 0;
  }
  else if (rhs == OPERATION_DIVIDE || rhs == OPERATION_REMINDER_OF_DIVISION || rhs == OPERATION_MULTIPLICATION)
  {
    rhs_prior = 1;
  }
  return (rhs_prior - lhs_prior);
}
