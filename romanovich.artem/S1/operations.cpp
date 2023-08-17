#include "operations.h"
#include <stdexcept>
#include "owerflowlongcheck.h"
char romanovich::as_char(romanovich::operations_t operation)
{
  return static_cast< char >(operation);
}
long long romanovich::doOperation(long long b, long long a, const operations_t &oper)
{
  if (oper == operations_t::plus)
  {
    if (!overflowAdd(a, b))
    {
      return a + b;
    }
    else
    {
      throw std::overflow_error("Overflow.");
    }
  }
  if (oper == operations_t::minus)
  {
    if (!overflowSubt(a, b))
    {
      return a - b;
    }
    else
    {
      throw std::overflow_error("Overflow.");
    }
  }
  if (oper == operations_t::multiplication)
  {
    if (!overflowMult(a, b))
    {
      return a * b;
    }
    else
    {
      throw std::overflow_error("Overflow.");
    }
  }
  if (oper == operations_t::division)
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
