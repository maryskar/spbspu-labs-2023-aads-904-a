#include "count_postfix.h"
#include "count.h"
#include "calculator.h"
#include <iostream>

void skarlygina::formatToPostfix(std::string& str, Queue< std::string >& queue)
{
  std::string operation;
  std::string operand;
  Stack< std::string > stack;
  size_t i = 0;

  while (i < str.length())
  {
    if (str[i] == '(')
    {
      operation = str[i];
      stack.push(operation);
      operation = "";
    }
    else if (str[i] == ')')
    {
      if (operand != "")
      {
        queue.push(operand);
        operand = "";
      }
      while (!stack.isEmpty() && stack.top() != "(")
      {
        queue.push(stack.top());
        stack.pop();
      }
      if (stack.top() == "(")
      {
        stack.pop();
      }
    }
    else if (std::isdigit(str[i]) && i == str.length() - 1)
    {
      operand += str[i];
      queue.push(operand);
      if (!stack.isEmpty())
      {
        queue.push(stack.top());
        stack.pop();
      }
      operand = "";
    }
    else if (std::isdigit(str[i]))
    {
      operand += str[i];
    }
    else if (str[i] == ' ' && std::isdigit(str[i - 1]))
    {
      queue.push(operand);
      operand = "";
    }
    else if (isOperation(str[i]))
    {
      operation = str[i];
      if (stack.isEmpty())
      {
        stack.push(operation);
        operation = "";
      }
      else if (!stack.isEmpty() || stack.top() != "(")
      {
        std::string operation2 = stack.top();
        if (!isGreaterPriority(operation[0], operation2[0]))
        {
          while (!stack.isEmpty() && stack.top() != "(" && (!isGreaterPriority(operation[0], stack.top()[0])))
          {
            queue.push(stack.top());
            stack.pop();
          }
          stack.push(operation);
          operation = "";
        }
        if (isGreaterPriority(operation[0], operation2[0]))
        {
          stack.push(operation);
          operation = "";
        }
      }
    }
    else if (i == str.length() - 1)
    {
      while (!stack.isEmpty())
      {
        queue.push(stack.top());
        stack.pop();
      }
      if (!operation.empty())
      {
        queue.push(operation);
      }
    }
    i++;
  }
  if (!stack.isEmpty())
  {
    queue.push(stack.top());
    stack.pop();
  }
}

void skarlygina::countPostfix(Queue< std::string >& queue, Stack< long long >& res)
{
  Stack< long long > stack;
  //std::cout << queue << "\n";
  while (!queue.isEmpty())
  {
    std::string first = queue.top();
    //std::cout << first << " queue top count\n";
    queue.pop();
    if (!skarlygina::checkString(first))
    {
      long long a = stack.top();
      stack.pop();
      long long b = stack.top();
      stack.pop();
      stack.push(switchSymbol(first, b, a));
      //std::cout << "a = " << b << "  b = " << a << "    res = " << switchSymbol(first, b, a) <<  "\n";
    }
    else
    {
      long long a = std::stoll(first);
      stack.push(a);
    }
  }
  std::cout << stack << " stack\n";
  res.push(stack.top());
}
