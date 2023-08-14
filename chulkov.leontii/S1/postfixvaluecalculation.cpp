#include "postfixvaluecalculation.h"
#include <limits>
#include "isoperator.h"
#include "stack.h"

namespace chulkov {
  long long max = std::numeric_limits< long long >::max();
  long long min = std::numeric_limits< long long >::min();

  bool isAddOverflow(long long frst, long long sec) {
    return (sec > 0 && frst > max - sec) || (sec < 0 && frst < min - sec);
  }

  bool isSubOverflow(long long frst, long long sec) {
    return (sec < 0 && frst > max + sec) || (sec > 0 && frst < min + sec);
  }

  bool isMultOverflow(long long frst, long long sec) {
    if (frst == 0 || sec == 0) {
      return false;
    }
    return frst > max / sec || frst < min / sec;
  }

  bool isOverflow(long long frst, long long sec, char op) {
    if (op == '+') {
      return isAddOverflow(frst, sec);
    } else if (op == '-') {
      return isSubOverflow(frst, sec);
    } else if (op == '*') {
      return isMultOverflow(frst, sec);
    }
    return false;
  }

  long long calculatePostfix(Queue< std::string > postfix) {
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
