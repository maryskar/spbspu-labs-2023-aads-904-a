#include "postfixvaluecalculation.h"
#include <cmath>
#include "isoperator.h"
#include "stack.h"

long long calculatePostfix(Queue< std::string > postfix)
{
  Stack< long long > op;

  while (!postfix.empty()) {
    std::string c = postfix.drop();
    if (std::isdigit(c[0])) {
      op.push(std::stoll(c));
    } else if (isOperator(c)) {
      if (op.empty()) {
        throw std::runtime_error("Error in expression");
      }
      long long operand2 = op.drop();
      if (op.empty()) {
        throw std::runtime_error("Error in expression");
      }
      long long operand1 = op.drop();
      long long result;
      switch (c[0]) {
      case '+':
        result = operand1 + operand2;
        break;
      case '-':
        result = operand1 - operand2;
        break;
      case '*':
        result = operand1 * operand2;
        break;
      case '/':
        result = operand1 / operand2;
        break;
      case '%':
        result = std::fmod(operand1, operand2);
        break;
      }
      op.push(result);
    } else {
      throw std::runtime_error("Error in expression");
    }
  }
  if (op.empty()) {
    throw std::runtime_error("Error in expression");
  }
  long long finalResult = op.drop();
  if (!op.empty()) {
    throw std::runtime_error("Error in expression");
  }
  return finalResult;
}
