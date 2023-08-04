#include "calculate.h"
#include <stdexcept>
#include <limits>
#include "stack.h"

constexpr long long maximum = std::numeric_limits< long long >::max();
constexpr long long minimum = std::numeric_limits< long long >::min();

long long azheganova::summarize(long long secondnum, long long firstnum)
{
  if ((firstnum * secondnum >= 0) && (firstnum >= 0))
  {
    if (maximum - firstnum >= secondnum)
    {
      return firstnum + secondnum;
    }
    else
    {
      throw std::overflow_error("overflow");
    }
  }
  if ((firstnum * secondnum >= 0) && (firstnum <= 0))
  {
    if (minimum - firstnum <= secondnum)
    {
      return firstnum + secondnum;
    }
    else
    {
      throw std::overflow_error("overflow");
    }
  }
  else
  {
    return firstnum + secondnum;
  }
}

long long azheganova::subtract(long long secondnum, long long firstnum)
{
  if ((firstnum > 0) && (minimum + firstnum > secondnum))
  {
    throw std::overflow_error("overflow");
  }
  return firstnum - secondnum;
}

long long azheganova::multiply(long long secondnum, long long firstnum)
{
  if ((firstnum * secondnum < 0) && (firstnum >= 0))
  {
    if (maximum / firstnum >= secondnum)
    {
      return firstnum * secondnum;
    }
    else
    {
      throw std::overflow_error("overflow");
    }
  }
  if ((firstnum * secondnum >= 0) && (firstnum <= 0))
  {
    if (minimum / firstnum >= secondnum)
    {
      return firstnum * secondnum;
    }
    else
    {
      throw std::overflow_error("overflow");
    }
  }
  else
  {
    return firstnum * secondnum;
  }
}

long long azheganova::divide(long long secondnum, long long firstnum)
{
  if (secondnum == 0)
  {
    throw std::logic_error("division by 0");
  }
  return firstnum / secondnum;
}

long long azheganova::calculateRemainder(long long secondnum, long long firstnum)
{
  if (secondnum == 0)
  {
    throw std::logic_error("division by 0");
  }
  if (firstnum < 0)
  {
    return (firstnum % secondnum) + secondnum;
  }
  return firstnum % secondnum;
}

long long azheganova::calculatePostfix(Queue< std::string > & postfix)
{
  Stack < long long > stack;
  while (!postfix.isEmpty())
  {
    std::string element;
    element = postfix.get();
    postfix.pop();
    if (std::isdigit(element[0]))
    {
      stack.push(std::stoll(element));
    }
    else
    {
      long long firstnum = stack.get();
      stack.pop();
      long long secondnum = stack.get();
      stack.pop();
      if (element == "+")
      {
        stack.push(summarize(firstnum, secondnum));
      }
      if (element == "-")
      {
        stack.push(subtract(firstnum, secondnum));
      }
      if (element == "*")
      {
        stack.push(multiply(firstnum, secondnum));
      }
      if (element == "/")
      {
        stack.push(divide(firstnum, secondnum));
      }
      if (element == "%")
      {
        stack.push(calculateRemainder(firstnum, secondnum));
      }
    }
  }
  return stack.get();
}
