#include "calculate.h"
#include <stdexcept>
#include <limits>
#include "stack.h"

long long summarize(long long secondnum, long long firstnum)
{
  long long maximum = std::numeric_limits< long long >::max();
  long long minimum = std::numeric_limits< long long >::min();
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

long long subtract(long long secondnum, long long firstnum)
{
  long long minimum = std::numeric_limits< long long >::min();
  if ((firstnum > 0) && (minimum + firstnum > secondnum))
  {
    throw std::overflow_error("overflow");
  }
  return firstnum - secondnum;
}

long long multiply(long long secondnum, long long firstnum)
{
  long long maximum = std::numeric_limits< long long >::max();
  long long minimum = std::numeric_limits< long long >::min();
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

long long divide(long long secondnum, long long firstnum)
{
  if (secondnum == 0)
  {
    throw std::logic_error("division by 0");
  }
  return firstnum / secondnum;
}

long long calculateRemainder(long long secondnum, long long firstnum)
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

long long calculatePostfix(azheganova::Queue <std::string> & postfix)
{
  azheganova::Stack < long long > stack;
  while (!postfix.isEmpty())
  {
    std::string element;
    element = postfix.drop();
    postfix.pop();
    if (std::isdigit(element[0]))
    {
      stack.push(std::stoll(element));
    }
    else
    {
      long long firstnum = stack.drop();
      stack.pop();
      long long secondnum = stack.drop();
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
  return stack.drop();
}
