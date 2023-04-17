#include "compare-operations-priority.hpp"

bool chemodurov::isLessPriority(chemodurov::operation_t lhs, chemodurov::operation_t rhs)
{
  int lhs_prior = 0;
  int rhs_prior = 0;
  if (lhs == operation_t::MINUS || lhs == operation_t::PLUS)
  {
    lhs_prior = 0;
  }
  else if (lhs == operation_t::DIVIDE || lhs == operation_t::REMINDER_OF_DIVISION || lhs == operation_t::MULTIPLICATION)
  {
    lhs_prior = 1;
  }
  if (rhs == operation_t::MINUS || rhs == operation_t::PLUS)
  {
    rhs_prior = 0;
  }
  else if (rhs == operation_t::DIVIDE || rhs == operation_t::REMINDER_OF_DIVISION || rhs == operation_t::MULTIPLICATION)
  {
    rhs_prior = 1;
  }
  return lhs_prior < rhs_prior;
}
