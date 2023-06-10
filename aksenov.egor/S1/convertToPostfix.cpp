#include "convertToPostfix.h"
#include "queue.h"
#include "stack.h"
bool isOperator(std::string oper)
{
  return oper == "+" || oper == "-" || oper == "*" || oper == "/" || oper == "%";
}
bool isNumeric(std::string const &str)
{
  char* p;
  strtol(str.c_str(), &p, 10);
  return *p == 0;
}
int getPriority(std::string operation)
{
  if (operation == "+" || operation == "-")
  {
    return 1;
  }
  else if (operation == "*" || operation == "/" || operation == "%")
  {
    return 2;
  }
  else
  {
    return 0;
  }
}
aksenov::Queue <std::string> aksenov::getPostfixQueue(aksenov::Queue< std::string > &infQueue)
{
  aksenov::Queue< std::string > postfixQueue;
  aksenov::Stack< std::string > stack;
  while (!infQueue.isEmpty())
  {
    std::string elem = infQueue.drop();
    infQueue.pop();
    if (elem == "(")
    {
      stack.push(elem);
    }
    else if(isNumeric(elem))
    {
      postfixQueue.push(elem);
    }
    else if (elem == ")") {
      while (!stack.isEmpty() && stack.drop() != "(") {
        postfixQueue.push(stack.drop());
        stack.pop();
      }
      stack.pop();
    }
    else if (isOperator(elem)) {
      if (!stack.isEmpty()) {
        while (getPriority(elem) <= getPriority(stack.drop())) {
          postfixQueue.push(stack.drop());
          stack.pop();
        }
        stack.push(elem);
      }
    }
    else {
      while (!stack.isEmpty() && getPriority(elem) <= getPriority(stack.drop())) {
        postfixQueue.push(stack.drop());
        stack.pop();
      }
      stack.push(elem);
    }
  }
  return postfixQueue;
}