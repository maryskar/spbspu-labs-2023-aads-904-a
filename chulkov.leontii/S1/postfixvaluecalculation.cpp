#include "postfixvaluecalculation.h"
#include <cmath>
#include <limits>
#include "isoperator.h"
#include "stack.h"


long long calculatePostfix(Queue< std::string > postfix) {
  Stack< long long > op;
  long long max = std::numeric_limits<long long>::max();
  long long min = std::numeric_limits<long long>::min();

  while (!postfix.empty()) {
    std::string c = postfix.drop();
    if (std::isdigit(c[0])) {
      try {
        long long val = std::stoll(c);
        if (val > max || val < min) {
          throw std::out_of_range("Overflow");
        }
        op.push(val);
      } catch (std::out_of_range& e) {
        throw std::out_of_range("Overflow");
      }
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
        if (operand2 == 0) {
          throw std::runtime_error("zero");
        }
        result = operand1 / operand2;
        break;
      case '%':
        if (operand2 == 0) {
          throw std::runtime_error("zero");
        }
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
