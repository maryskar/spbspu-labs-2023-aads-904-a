#include "calculateInPostfixQueue.h"
#include <stdexcept>
#include "stack.h"
#include "symbols.h"
#include "calculate.h"

long long fesenko::calculateInPostfixQueue(Queue< std::string > &postfixQueue)
{
  Stack< long long > stack;
  long long result = 0;
  while (!postfixQueue.isEmpty()) {
    std::string element = postfixQueue.front();
    postfixQueue.pop();
    if (isNumber(element)) {
      stack.push(std::stoll(element));
    } else {
      long long b = stack.top();
      stack.pop();
      long long a = stack.top();
      stack.pop();
      result = calculate(a, b, element);
      stack.push(result);
    }
  }
  result = stack.top();
  stack.pop();
  return result;
}
