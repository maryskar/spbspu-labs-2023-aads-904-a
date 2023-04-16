#include "calculate.h"
#include <stdexcept>
#include <limits>
#include "checkingfordigit.h"

long long maximum = std::numeric_limits< long long >::max();
long long minimum = std::numeric_limits< long long >::min();
void calculatePostfix(Queue< std::string > & postfix, Stack< std::string > & answer, Stack< std::string > & stack)
{
  stack.push(postfix.drop());
  postfix.pop();
  while (!stack.isEmpty())
  {
    std::string element;
    if (!postfix.isEmpty())
    {
      element = postfix.drop();
      postfix.pop();
    }
    if (isdigit(element[0]))
    {
      stack.push(element);
    }
    else
    {
      long long secondnum = std::stoll(stack.drop(), nullptr, 10);
      stack.pop();
      long long firstnum = std::stoll(stack.drop(), nullptr, 10);
      stack.pop();
      std::string calcres;
      if (element == "+")
      {
        if ((firstnum * secondnum >= 0) && (firstnum >= 0))
        {
          if (maximum - firstnum >= secondnum)
          {
            calcres = firstnum + secondnum;
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
            calcres = firstnum + secondnum;
          }
          else
          {
            throw std::overflow_error("overflow");
          }
        }
        else
        {
          calcres = firstnum + secondnum;
        }
      }
      else if (element == "-")
      {
        calcres = firstnum - secondnum;
      }
      else if (element == "*")
      {
        if ((firstnum * secondnum < 0) && (firstnum >= 0))
        {
          if (maximum / firstnum >= secondnum)
          {
            calcres = firstnum * secondnum;
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
            calcres = firstnum * secondnum;
          }
          else
          {
            throw std::overflow_error("overflow");
          }
        }
        else
        {
          calcres = firstnum * secondnum;
        }
      }
      else if (element == "/")
      {
        if (secondnum == 0)
        {
          throw std::logic_error("division by 0");
        }
        calcres = firstnum / secondnum;
      }
      else if (element == "%")
      {
        if (secondnum == 0)
        {
          throw std::logic_error("division by 0");
        }
        if (firstnum < 0)
        {
          calcres = firstnum % secondnum + secondnum;
        }
        calcres = firstnum % secondnum;
      }
      stack.push(calcres);
    }
  }
  answer.push(stack.drop());
}
