#include "infixQueueToPostfixQueue.h"
#include <string>
#include <stdexcept>
#include "stack.h"
#include "queue.h"
#include "symbols.h"

fesenko::Queue< std::string > fesenko::infixQueueToPostfixQueue(fesenko::Queue < std::string > &infixQueue)
{
  fesenko::Stack< std::string > stack;
  fesenko::Queue< std::string > postfixQueue;
  while (!infixQueue.isEmpty()) {
    std::string element = infixQueue.front();
    if (isNumber(element)) {
      postfixQueue.push(element);
    }
    if (isOperation(element)) {
      while (!stack.isEmpty() && priority(element) >= priority(stack.top()) && !isOpenedBracket(stack.top())) {
        postfixQueue.push(stack.top());
        stack.pop();
      }
      stack.push(infixQueue.front());
      infixQueue.pop();
    }
    if (isOpenedBracket(element)) {
      stack.push(element);
      infixQueue.pop();
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
