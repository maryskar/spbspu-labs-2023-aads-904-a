#include "operations.h"
#include <stdexcept>
#include "owerflowlongcheck.h"
char romanovich::as_char(romanovich::operations_t operation)
{
  return static_cast<char>(operation);
}
long long romanovich::doOperation(long long b, long long a, const romanovich::operations_t &oper)
{
  if (oper == romanovich::operations_t::plus)
  {
    if (!romanovich::overflowAdd(a, b))
    {
      return a + b;
    }
    else
    {
      throw std::overflow_error("Overflow.");
    }
  }
  if (oper == romanovich::operations_t::minus)
  {
    if (!romanovich::overflowSubt(a, b))
    {
      return a - b;
    }
    else
    {
      throw std::overflow_error("Overflow.");
    }
  }
  if (oper == romanovich::operations_t::multiplication)
  {
    if (!romanovich::overflowMult(a, b))
    {
      return a * b;
    }
    else
    {
      throw std::overflow_error("Overflow.");
    }
  }
  if (oper == romanovich::operations_t::division)
  {
    if (b != 0)
    {
      return a / b;
    }
    else
    {
      throw std::overflow_error("Overflow.");
    }
  }
  if (a < 0)
  {
    return ((a % b) + b);
  }
  return a % b;
}
