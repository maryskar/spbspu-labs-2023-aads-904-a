#include "calculate.h"
#include <stdexcept>
#include "stack.h"


long long calculatePostfix(Queue<std::string>& postfixQueue)
{
  Stack< long long > stack;
  while (!postfixQueue.isEmpty())
  {
    std::string token = postfixQueue.drop();
    postfixQueue.pop();
    if (isdigit(token[0]))
    {
      stack.push(std::stoll(token));
    }
    else
    {
      long long secondnum = stack.drop();
      stack.pop();
      long long firstnum = stack.drop();
      stack.pop();
      long long result;
      if (token == "+")
      {
        result = firstnum + secondnum;
      }
      else if (token == "-")
      {
        result = firstnum - secondnum;
      }
      else if (token == "*")
      {
        result = firstnum * secondnum;
      }
      else if (token == "/")
      {
        if (secondnum == 0)
        {
          throw std::logic_error("division by 0");
        }
        result = firstnum / secondnum;
      }
      else if (token == "%")
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