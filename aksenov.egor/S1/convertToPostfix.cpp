#include "convertToPostfix.h"
#include "queue.h"
#include "stack.h"
#include "details.h"

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
      if( !stack.isEmpty() && stack.drop() == "(")
      {
        stack.pop();
      }
      else
      {
        throw std::invalid_argument("wrong brackets");
      }
    }
    else if (isOperator(elem)) {
      while (!stack.isEmpty() && isOperator(stack.drop()) && getPriority(elem) <= getPriority(stack.drop())) {
        postfixQueue.push(stack.drop());
        stack.pop();
      }
      stack.push(elem);
    }
    else {
      throw std::invalid_argument("wrong input");
    }
  }
  while ( !stack.isEmpty())
  {
    if(stack.drop() == "(" || stack.drop() == ")")
    {
      throw std::invalid_argument("wrong brackets");
    }
    postfixQueue.push(stack.drop());
    stack.pop();
  }
  return postfixQueue;
}