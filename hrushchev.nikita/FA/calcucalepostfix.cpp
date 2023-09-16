#include "calcucalepostfix.hpp"
#include <string>
#include <cmath>
#include "queue.hpp"
#include "stack.hpp"
#include "arithmetic.hpp"

long double hrushchev::calculatePostfix(hrushchev::Queue< std::string >& postfixQueue)
{
  namespace hrn = hrushchev;

  hrn::Stack< long double > stack;
  while (!postfixQueue.isEmpty())
  {
    std::string token = postfixQueue.get();
    postfixQueue.pop();
    if (std::isdigit(token[0]))
    {
      stack.push(std::stold(token));
    }
    else if (token == "sin" || token == "cos")
    {
      if (stack.isEmpty())
      {
        throw std::logic_error("Not enough operands for unary operator");
      }
      long double operand = stack.get();
      stack.pop();
      long double result;
      if (token == "sin")
      {
        result = hrn::sin(operand);
      }
      else if (token == "cos")
      {
        result = hrn::cos(operand);
      }
      stack.push(result);
    }
    else
    {
      long double operand2 = stack.get();
      stack.pop();
      long double operand1 = stack.get();
      stack.pop();
      long double result;
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


