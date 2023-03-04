#include <iostream>
#include <fstream>
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
    //std::cout << "queue: ";
    //queue.print();
    //std::cout << "stack: ";
    //stack->print();
    //std::cout << "result: ";
    //postfixQueue.print();
    //std::cout << "\n";
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
    return std::to_string(a + b);
  }
  if (oper == "-")
  {
    return std::to_string(a - b);
  }
  if (oper == "*")
  {
    return std::to_string(a * b);
  }
  if (oper == "/")
  {
    return std::to_string(a / b);
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
  if (argc == 2)
  {
    std::string fileIn = argv[1];
    std::fstream fileInput(fileIn);
    if (!fileInput.is_open())
    {
      std::cerr << "Error while opening file " << fileIn << ".\n";
      return 1;
    }
    for (std::string line; std::getline(fileInput, line);)
    {
      std::cout << line << "\n";
    }
  }
  else
  {
    for (std::string line; std::getline(std::cin, line);)
    {
      Queue< std::string > infixNotation = splitLine(line);
      Queue< std::string > postfixQueue = getPostfixFromInfix(infixNotation);
      /////////////////////////////postfixQueue.print();
      /////////////////////////////std::cout << "!!!\n";

      ///
      Stack< std::string > *stack = new Stack< std::string >;
      stack->push(postfixQueue.pop());
      while (stack->getSize() >= 1)
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
        //std::cout << "  " << el << std::endl;
        //stack->print();
        //std::cout << "\n";
        if (isDigit(el))
        {
          stack->push(el);
        }
        else
        {
          std::string x = stack->pop();
          std::string y = stack->pop();
          stack->push(doOperation(std::stol(x, nullptr, 10), std::stol(y, nullptr, 10), el));
        }
      }
      ///

      std::cout << std::stol(stack->top_->data_, nullptr, 10);
      //std::cout << calcPostfixExpression(infixNotation);
    }
  }
  return 0;
}
