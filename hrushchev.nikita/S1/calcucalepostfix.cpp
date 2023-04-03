#include "calcucalepostfix.hpp"
#include <string>
#include <stdexcept>
#include <limits>
#include "queue.hpp"
#include "stack.hpp"


long long sum(long long a, long long b)
{
  const long long max = std::numeric_limits< int long long >::max();
  if(max - a > b)
  {
    throw std::overflow_error("Sum overflow");
  }
  return a + b
}

long long calculatePostfix(Queue<std::string>& postfixQueue)
{
  Stack< int > stack;
  while (!postfixQueue.isEmpty())
  {
    std::string token = postfixQueue.get();
    postfixQueue.pop();
    if (isdigit(token[0]))
    {
      stack.push(std::stoi(token));
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
        result = sum(operand1, operand2)
      }
      else if (token == "-")
      {
        result = subtraction(operand1, operand2)
      }
      else if (token == "*")
      {
        result = operand1 * operand2;
      }
      else if (token == "/")
      {
        result = operand1 / operand2;
      }
      else
      {
        std::logic_error("Ivalid token");
      }
      stack.push(result);
    }
  }
  return stack.get();
}

