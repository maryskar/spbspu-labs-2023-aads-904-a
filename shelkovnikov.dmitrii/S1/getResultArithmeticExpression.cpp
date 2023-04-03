#include "getResultArithmeticExpression.h"
#include <limits>
#include <stdexcept>
#include "stack.h"
namespace
{
  constexpr long long max_long_long = std::numeric_limits< long long >::max();
  constexpr long long min_long_long = std::numeric_limits< long long >::min();
  namespace
  {
    bool isOverAdd(long long first, long long second)
    {
      return first > 0 && second > 0 && second > (max_long_long - first);
    }
    bool isUnderAdd(long long first, long long second)
    {
      return first < 0 && second < 0 && first < (min_long_long - second);
    }
    bool isOverMult(long long first, long long second)
    {
      return (first > max_long_long / second) && ((first > 0 && second > 0) || (first < 0 && second < 0));
    }
    bool isUnderMult(long long first, long long second)
    {
      return (first < min_long_long / second) && ((first > 0 && second < 0) || (first < 0 && second > 0));
    }
  }
  bool isOverflowedAdd(long long first, long long second)
  {
    return isOverAdd(first, second) || isUnderAdd(first, second);
  }
  bool isOverflowedMult(long long first, long long second)
  {
    return isOverMult(first, second) || isUnderMult(first, second);
  }
}
long long details::getResult(long long first, long long second, char oper)
{
  if (oper == '+')
  {
    if (isOverflowedAdd(first, second))
    {
      throw std::logic_error("Overflow");
    }
    return first + second;
  }
  if (oper == '-')
  {
    if (isOverflowedAdd(first, second))
    {
      throw std::logic_error("Overflow");
    }
    return first - second;
  }
  if (oper == '*')
  {
    if (isOverflowedMult(first, second))
    {
      throw std::logic_error("Overflow");
    }
    return first * second;
  }
  if (oper == '/')
  {
    if (second == 0)
    {
      throw std::logic_error("Division by 0");
    }
    return first / second;
  }
  if (oper == '%')
  {
    if (first > 0)
    {
      return first % second;
    }
    else
    {
      return second - (-first) % second;
    }
  }
  throw std::logic_error("Not supported this operator");
}
long long dimkashelk::getResultArithmeticExpression(dimkashelk::Queue< dimkashelk::PartOfArithExpr > &polandExpression)
{
  namespace dsk = dimkashelk;
  dsk::Stack< dsk::PartOfArithExpr > remains;
  while (!polandExpression.empty())
  {
    dsk::PartOfArithExpr p = polandExpression.front();
    polandExpression.pop_front();
    if (p.isDigit)
    {
      remains.push(p);
    }
    else
    {
      dsk::PartOfArithExpr p2 = remains.last();
      remains.pop_back();
      dsk::PartOfArithExpr p1 = remains.last();
      remains.pop_back();
      remains.push(dsk::PartOfArithExpr(details::getResult(p1.element.operand_, p2.element.operand_, p.element.operator_)));
    }
  }
  auto res = remains.last().element.operand_;
  remains.pop_back();
  return res;
}
