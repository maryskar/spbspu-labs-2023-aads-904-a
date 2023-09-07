#include "convertToPostfix.h"
#include "queue.h"
#include "stack.h"
#include "details.h"

aksenov::Queue< std::string > aksenov::getPostfixQueue(aksenov::Queue< std::string > &infQueue)
{
  Queue< std::string > postfixQueue;
  Stack< std::string > stack;
  while (!infQueue.isEmpty())
  {
    std::string elem = infQueue.get();
    infQueue.pop();
    if (elem == "(")
    {
      stack.push(elem);
    }
    else if (aksenov::isNumeric(elem))
    {
      postfixQueue.push(elem);
    }
    else if (elem == ")") {
      while (!stack.isEmpty() && stack.get() != "(") {
        postfixQueue.push(stack.get());
        stack.pop();
      }
      if (!stack.isEmpty() && stack.get() == "(")
      {
        stack.pop();
      }
      else
      {
        throw std::invalid_argument("wrong brackets");
      }
    }
    else if (aksenov::isOperator(elem)) {
      while (!stack.isEmpty() && aksenov::isOperator(stack.get()) && aksenov::isloverOrSamePriority(elem,stack.get()))
      {
        postfixQueue.push(stack.get());
        stack.pop();
      }
      stack.push(elem);
    }
    else
    {
      throw std::invalid_argument("wrong input");
    }
  }
  while ( !stack.isEmpty())
  {
    if(stack.get() == "(" || stack.get() == ")")
    {
      throw std::invalid_argument("wrong brackets");
    }
    postfixQueue.push(stack.get());
    stack.pop();
  }
  return postfixQueue;
}
