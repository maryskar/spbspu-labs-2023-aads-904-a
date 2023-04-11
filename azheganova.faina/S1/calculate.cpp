#include "calculate.h"
#include <stdexcept>
#include <limits>
#include "stack.h"

long long maximum = std::numeric_limits< long long >::max();
long long minimum = std::numeric_limits< long long >::min();
long long calculatePostfix(Queue<std::string> & postfix)
{
  Stack< long long > stack;
  while (!postfix.isEmpty())
  {
    std::string element = postfix.drop();
    postfix.pop();
    if (isdigit(element[0]))
    {
      stack.push(std::stoll(element));
    }
    else
    {
      long long secondnum = stack.drop();
      stack.pop();
      long long firstnum = stack.drop();
      stack.pop();
      long long result;
      if (element == "+")
      {
        result = firstnum + secondnum;
      }
      else if (element == "-")
      {
        result = firstnum - secondnum;
      }
      else if (element == "*")
      {
        if ((firstnum * secondnum < 0) && (firstnum >= 0))
        {
          if (maximum / firstnum >= secondnum)
          {
            result = firstnum * secondnum;
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
            result = firstnum * secondnum;
          }
          else
          {
            throw std::overflow_error("overflow");
          }
        }
        else
        {
          result = firstnum * secondnum;
        }
      }
      else if (element == "/")
      {
        if (secondnum == 0)
        {
          throw std::logic_error("division by 0");
        }
        result = firstnum / secondnum;
      }
      else if (element == "%")
      {
        if (secondnum == 0)
        {
          throw std::logic_error("division by 0");
        }
        if(firstnum < 0)
        {
          return secondnum + firstnum % secondnum;
        }
        return firstnum % secondnum;
      }
      stack.push(result);
    }
  }
  return stack.drop();
}
