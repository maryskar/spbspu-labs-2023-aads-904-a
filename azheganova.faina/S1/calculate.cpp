#include "calculate.h"
#include <stdexcept>
#include "stack.h"


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
        result = firstnum * secondnum;
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
