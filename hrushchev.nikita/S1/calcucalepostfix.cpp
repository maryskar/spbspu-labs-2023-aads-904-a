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
  return a + b;
}

long long subtract(long long a, long long b)
{
  const long long min = std::numeric_limits< int long long >::min();
  if(min - a < b)
  {
    throw std::overflow_error("Subtraction overflow");
  }
  return a - b;
}

long long multiply(long long a, long long b)
{
  const long long max = std::numeric_limits< int long long >::max();
  const long long min = std::numeric_limits< int long long >::min();
  if((a > 0) && ((max / a) > b))
  {
    throw std::overflow_error("Multiply overflow");
  }
  else if((a < 0) && ((max / a) < b))
  {
    throw std::overflow_error("Multiply overflow");
  }  
  else if((a > 0) && ((min / a) < b))
  {
    throw std::overflow_error("Multiply overflow");
  }
  else if((a < 0) && ((min / a) > b))
  {
    throw std::overflow_error("Multiply overflow");
  }
  return a * b;
}

long long division(long long a, long long b)
{
  if(b == 0)
  {
    throw std::logic_error("Division by 0");
  }
  return a / b;
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
      else
      {
        std::logic_error("Ivalid token");
      }
      stack.push(result);
    }
  }
  return stack.get();
}

