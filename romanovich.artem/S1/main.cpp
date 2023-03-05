#include <iostream>
#include <fstream>
#include <limits>
#include "stack.h"
#include "queue.h"
#include "node.h"
///#include "notations.h"
//
//
//
//
//
//
//
long long maxLongLong = std::numeric_limits< long long >::max();
long long minLongLong = std::numeric_limits< long long >::min();
bool overflowAdd(long long a, long long b)
{
  return ((b > 0 && a > maxLongLong - b) || (b < 0 && a < minLongLong - b));
}
bool overflowMult(long long a, long long b)
{
  return ((a != 0 && b != 0) && ((a > maxLongLong / b) || (a < minLongLong / b)));
}
bool overflowSubt(long long a, long long b)
{
  return ((b < 0 && a > maxLongLong + b) || (b > 0 && a < minLongLong + b));
}
///
bool isOperator(const std::string &c)
{
  return (c == "+" || c == "-" || c == "*" || c == "/" || c == "%");
}
bool isDigit(const std::string &str)
{
  return std::all_of(str.begin(), str.end(), ::isdigit);
}
bool operationStackPopCondition(const std::string &q, const std::string &s)
{
  return ((q == "+" || q == "-") && (s == "*" || s == "/" || s == "%"));
}
Queue< std::string > getPostfixFromInfix(Queue< std::string > queue)
{
  Queue< std::string > postfixQueue;
  Stack< std::string > *stack = new Stack< std::string >;
  while (!queue.isEmpty() or !stack->isEmpty())
  {
    if (!queue.isEmpty())
    {
      std::string qEl = queue.pop();
      if (qEl == "(")
      {
        stack->push(qEl);
      }
      if (qEl == ")")
      {
        while (stack->top_->data_ != "(")
        {
          postfixQueue.push(stack->pop());
          if (stack->isEmpty())
          {
            break;
          }
        }
        stack->pop();
      }
      if (std::all_of(qEl.begin(), qEl.end(), ::isdigit))
      {
        postfixQueue.push(qEl);
      }
      if (isOperator(qEl))
      {
        if (!stack->isEmpty())
        {
          if (operationStackPopCondition(qEl, stack->top_->data_))
          {
            postfixQueue.push(stack->pop());
          }
        }
        stack->push(qEl);
      }
    }
    else
    {
      while (!stack->isEmpty())
      {
        postfixQueue.push(stack->pop());
      }
    }
  }
  delete stack;
  return postfixQueue;
}
Queue< std::string > splitLine(const std::string &string)
{
  Queue< std::string > queue;
  int begin = 0;
  int end = string.find(' ');
  while (end != -1)
  {
    queue.push(string.substr(begin, end - begin));
    begin = end + 1;
    end = string.find(' ', begin);
  }
  queue.push(string.substr(begin, end - begin));
  return queue;
}
std::string doOperation(long long b, long long a, const std::string &oper)
{
  if (oper == "+")
  {
    if (!overflowAdd(a, b))
    {
      return std::to_string(a + b);
    }
    else
    {
      throw std::overflow_error("");
    }
  }
  if (oper == "-")
  {
    if (!overflowSubt(a, b))
    {
      return std::to_string(a - b);
    }
    else
    {
      throw std::overflow_error("");
    }
  }
  if (oper == "*")
  {
    if (!overflowMult(a, b))
    {
      return std::to_string(a * b);
    }
    else
    {
      throw std::overflow_error("");
    }
  }
  if (oper == "/")
  {
    if (b != 0)
    {
      return std::to_string(a / b);
    }
    else
    {
      throw std::overflow_error("");
    }
  }
  return std::to_string(a % b);
}
//
//
//
//
//
//
//
int main(int argc, char **argv)
{
  if ((argc != 1) && (argc != 2))
  {
    std::cerr << "Not appropriate parameters number.\n";
    return 1;
  }
  Stack< std::string > stack = Stack< std::string >();
  std::fstream fileInput;
  if (argc == 2)
  {
    fileInput.open(argv[1]);
    if (!fileInput.is_open())
    {
      std::cerr << "Error while opening file.\n";
      return 1;
    }
    std::cin.rdbuf(fileInput.rdbuf());
  }
  Stack< std::string > answer;
  for (std::string line; std::getline(std::cin, line);)
  {
    Queue< std::string > infixNotation = splitLine(line);
    Queue< std::string > postfixQueue = getPostfixFromInfix(infixNotation);
    Stack< std::string > *calcStack = new Stack< std::string >;
    calcStack->push(postfixQueue.pop());
    while (calcStack->getSize() >= 1)
    {
      std::string el;
      if (!postfixQueue.isEmpty())
      {
        el = postfixQueue.pop();
      }
      else
      {
        break;
      }
      if (isDigit(el))
      {
        calcStack->push(el);
      }
      else
      {
        try
        {
          std::string x = calcStack->pop();
          std::string y = calcStack->pop();
          calcStack->push(doOperation(std::stol(x, nullptr, 10), std::stol(y, nullptr, 10), el));
        }
        catch (...)
        {
          delete calcStack;
          std::cerr << "Error while calc.\n";
          return 2;
        }
      }
    }
    answer.push(calcStack->top_->data_);
    delete calcStack;
  }
  if (!answer.isEmpty())
  {
    std::cout << answer.pop();
    while (!answer.isEmpty())
    {
      std::cout << " " << answer.pop();
    }
    std::cout << "\n";
  }
  return 0;
}
