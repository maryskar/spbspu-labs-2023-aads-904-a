#include "postfixvaluecalculation.h"
#include <cmath>
#include <limits>
#include "isoperator.h"
#include "stack.h"

namespace chulkov {
  bool isOverflow(long long a, long long b, char op) {
    long long max = std::numeric_limits<long long>::max();
    long long min = std::numeric_limits<long long>::min();
    if (op == '+' || op == '-') {
      if ((b > 0 && a > max - b) || (b < 0 && a < min - b)) {
        return true;
      }
    } else if (op == '*') {
      if (a > 0 && b > 0 && a > max / b) {
        return true;
      }
      if (a < 0 && b < 0 && a < max / b) {
        return true;
      }
      if (a < 0 && b > 0 && a < min / b) {
        return true;
      }
      if (a > 0 && b < 0 && b < min / a) {
        return true;
      }
    }
    return false;
  }

  long long calculatePostfix(chulkov::Queue< std::string > postfix) {
    chulkov::Stack< long long > op;

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
          if (isOverflow(operand1, operand2, '+')) {
            throw std::runtime_error("Overflow");
          }
          result = operand1 + operand2;
          break;
        case '-':
          if (isOverflow(operand1, operand2, '-')) {
            throw std::runtime_error("Overflow");
          }
          result = operand1 - operand2;
          break;
        case '*':
          if (isOverflow(operand1, operand2, '*')) {
            throw std::runtime_error("Overflow");
          }
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
          result = operand1 % operand2;
          if (result < 0) {
            result += std::abs(operand2);
          }
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
}
