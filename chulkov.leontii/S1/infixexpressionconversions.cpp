#include "infixexpressionconversions.h"
#include <string>
#include "queue.h"
#include "stack.h"

bool isOperator(char c)
{
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

int getPriority(char c)
{
  if (c == '+' || c == '-') {
    return 1;
  } else if (c == '*' || c == '/' || c == '%') {
    return 2;
  }
  return 0;
}

template < typename T >
std::string infixToPostfix(const std::string& infix)
{
  std::string post;
  Queue< T > out;
  Stack< T > op;

  for (T c : infix) {
    if (c == ' ') {
      continue;
    }
    if (std::isdigit(c)) {
      post += c;
    } else if (c == '(')  {
      op.push(c);
    } else if (c == ')') {
      while (!op.empty() && op.top_ != '(') {
        out.push(op.top_());
        op.pop();
      }
      if (!op.empty() && op.top_() == '(') {
        op.pop();
      } else {
        throw std::runtime_error("Leee, you have extra brackets");
      }
    } else {
      throw std::runtime_error("FuF, invalid character in expression");
    }
  }
}
