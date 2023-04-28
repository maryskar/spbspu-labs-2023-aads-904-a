#include "calcucalepostfix.hpp"
#include <string>
#include "queue.hpp"
#include "stack.hpp"
#include "arithmetic.hpp"

namespace hr = hrushchev;

long long hr::calculatePostfix(hr::Queue< std::string >& postfixQueue)
{
  hr::Stack< long long > stack;
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
        result = hr::sum(operand1, operand2);
      }
      else if (token == "-")
      {
        result = hr::subtract(operand1, operand2);
      }
      else if (token == "*")
      {
        result = hr::multiply(operand1, operand2);
      }
      else if (token == "/")
      {
        result = hr::division(operand1, operand2);
      }
      else if (token == "%")
      {
        result = hr::remaind(operand1, operand2);
      }
      stack.push(result);
    }
  }
  return stack.get();
}

