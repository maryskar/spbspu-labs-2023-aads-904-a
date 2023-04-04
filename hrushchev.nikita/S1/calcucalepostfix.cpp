#include "calcucalepostfix.hpp"
#include <string>
#include "queue.hpp"
#include "stack.hpp"
#include "arithmetic.hpp"

long long calculatePostfix(Queue<std::string>& postfixQueue)
{
  Stack< long long > stack;
  while (!postfixQueue.isEmpty())
  {
    std::string token = postfixQueue.get();
    postfixQueue.pop();
    if (isdigit(token[0]))
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
        result = sum(operand1, operand2);
      }
      else if (token == "-")
      {
        result = subtract(operand1, operand2);
      }
      else if (token == "*")
      {
        result = multiply(operand1, operand2);
      }
      else if (token == "/")
      {
        result = division(operand1, operand2);
      }
      else if (token == "%")
      {
        result = remaind(operand1, operand2);
      }
      stack.push(result);
    }
  }
  return stack.get();
}

