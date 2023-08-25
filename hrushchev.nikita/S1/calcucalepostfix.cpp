#include "calcucalepostfix.hpp"
#include <string>
#include <queue.hpp>
#include <stack.hpp>
#include <arithmetic.hpp>

long long hrushchev::calculatePostfix(hrushchev::Queue< std::string >& postfixQueue)
{
  namespace hrn = hrushchev;

  hrn::Stack< long long > stack;
  while (!postfixQueue.isEmpty())
  {
    std::string token = postfixQueue.get();
    postfixQueue.pop();
    if (std::isdigit(token[0]))
    {
      stack.push(std::stoll(token));
    }
    else
    {
      long long operand2 = stack.get();
      stack.pop();
      long long operand1 = stack.get();
      stack.pop();
      long long result;
      if (token == "+")
      {
        result = hrn::sum(operand1, operand2);
      }
      else if (token == "-")
      {
        result = hrn::subtract(operand1, operand2);
      }
      else if (token == "*")
      {
        result = hrn::multiply(operand1, operand2);
      }
      else if (token == "/")
      {
        result = hrn::division(operand1, operand2);
      }
      else if (token == "%")
      {
        result = hrn::remaind(operand1, operand2);
      }
      stack.push(result);
    }
  }
  return stack.get();
}

