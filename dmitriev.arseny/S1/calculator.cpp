#include "calculator.h"
#include "stack.h"
#include "queue.h"

#include <string>
#include <limits>

constexpr long long longLongMin = std::numeric_limits< long long >::min();
constexpr long long longLongMax = std::numeric_limits< long long >::max();

size_t definePriority(std::string inp);
std::string calculate(std::string s2, std::string s1, std::string symbol);
Queue< std::string > getQueueFromInput(std::string stringInp);
std::string drop(Queue< std::string >& queue);
std::string drop(Stack< std::string >& stack);

long long calculateTheExpression(std::string stringInp)
{
  Queue< std::string > infQueue;
  Stack< std::string > postStack;
  Stack< std::string > stack;

  infQueue = getQueueFromInput(stringInp);

  while (!infQueue.isEmpty())
  {
    if (infQueue.getTopData() == "(")
    {
      stack.push(drop(infQueue));
    }
    else if (infQueue.getTopData() == ")")
    {
      while (!(stack.getTopData() == "("))
      {
        postStack.push(drop(stack));
        postStack.push(calculate(drop(postStack), drop(postStack), drop(postStack)));
      }
      stack.popBack();
      infQueue.popBack();
    }
    else if (definePriority(infQueue.getTopData()) > 0)
    {
      if (stack.isEmpty() || (definePriority(infQueue.getTopData()) > definePriority(stack.getTopData())))
      {
        stack.push(drop(infQueue));
      }
      else
      {
        postStack.push(drop(stack));
        postStack.push(calculate(drop(postStack), drop(postStack), drop(postStack)));
        stack.push(drop(infQueue));
      }
    }
    else
    {
      postStack.push(drop(infQueue));
    }
  }
  while (!stack.isEmpty())
  {
    if ((stack.getTopData() == "(") || (stack.getTopData() == ")"))
    {
      throw std::logic_error("logic_error");
    }
    postStack.push(drop(stack));
    postStack.push(calculate(drop(postStack), drop(postStack), drop(postStack)));
  }

  return std::stoll(drop(postStack));
}

size_t definePriority(std::string inp)
{
  size_t priority = 0;
  if ((inp == "+") || (inp == "-"))
  {
    priority = 1;
  }
  else if (inp == "%")
  {
    priority = 2;
  }
  else if ((inp == "*") || (inp == "/"))
  {
    priority = 3;
  }

  return priority;
}

std::string calculate(std::string s2, std::string s1, std::string symbol)
{
  long long p1 = std::stoll(s1);
  long long p2 = std::stoll(s2);
  long long result = 0.0;

  if (symbol == "+")
  {
    if (p2 > 0 && p1 > longLongMax - p2)
    {
      throw std::overflow_error("overflow_error");
    }
    if (p2 < 0 && p1 < longLongMin - p2)
    {
      throw std::underflow_error("underflow_error");
    }
    result = p2 + p1;
  }
  else if (symbol == "-")
  {
    if (p1 < 0 && p2 > longLongMax + p1)
    {
      throw std::overflow_error("overflow_error");
    }
    if (p1 > 0 && p2 < longLongMin + p1)
    {
      throw std::underflow_error("underflow_error");
    }
    result = p2 - p1;
  }
  else if (symbol == "*")
  {
    if ((p2 > 0 && p1 > longLongMax / p2) || (p2 < 0 && p1 > longLongMax / p2))
    {
      throw std::overflow_error("overflow_error");
    }
    if ((p2 < 0 && p1 > longLongMin / p2) || (p2 > 0 && p1 > longLongMax / p2))
    {
      throw std::underflow_error("underflow_error");
    }
    result = p2 * p1;
  }
  else if (symbol == "/")
  {
    if (p1 == 0)
    {
      throw std::logic_error("div on zero");
    }
    result = p2 / p1;
  }
  else if (symbol == "%")
  {
    if (p1 == 0)
    {
      throw std::logic_error("mod on zero");
    }
    result = p2 % p1;
    if (result < 0)
    {
      result += p1;
    }
  }

  return std::to_string(result);
}

Queue< std::string > getQueueFromInput(std::string stringInp)
{
  Queue< std::string > infQueue;
  std::string curr = "";

  for (size_t i = 0; stringInp[i] != '\0'; i++)
  {
    if (stringInp[i] == ' ')
    {
      infQueue.push(curr);
      curr = "";
    }
    else
    {
      curr = curr + stringInp[i];
    }
  }
  infQueue.push(curr);

  return infQueue;
}

std::string drop(Queue< std::string >& queue)
{
  std::string currentData = queue.getTopData();
  queue.popBack();

  return currentData;
}

std::string drop(Stack< std::string >& stack)
{
  std::string currentData = stack.getTopData();
  stack.popBack();

  return currentData;
}
