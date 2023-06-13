#include "infixQueueToPostfixQueue.h"
#include <stdexcept>
#include "stack.h"
#include "symbols.h"

fesenko::Queue< std::string > fesenko::infixQueueToPostfixQueue(Queue< std::string > &infixQueue)
{
  fesenko::Stack< std::string > stack;
  fesenko::Queue< std::string > postfixQueue;
  while (!infixQueue.isEmpty()) {
    std::string element = infixQueue.front();
    infixQueue.pop();
    if (isNumber(element)) {
      postfixQueue.push(element);
    }
    if (isOperation(element)) {
      while (!stack.isEmpty() && !isOpenedBracket(stack.top()) && priority(element) >= priority(stack.top())) {
        postfixQueue.push(stack.top());
        stack.pop();
      }
      stack.push(element);
    }
    if (isOpenedBracket(element)) {
      stack.push(element);
    }
    if (isClosedBracket(element)) {
      while (!isOpenedBracket(stack.top())) {
        postfixQueue.push(stack.top());
        stack.pop();
        if (stack.isEmpty()) {
          throw std::logic_error("Incorrect expression");
        }
      }
      stack.pop();
    }
  }
  while (!stack.isEmpty()) {
    if (isOpenedBracket(stack.top())) {
      throw std::logic_error("Incorrect expression");
    }
    postfixQueue.push(stack.top());
    stack.pop();
  }
  return postfixQueue;
}
