#include "computestr.h"
#include <limits>

Queue< std::string > split(std::string in)
{
  Queue< std::string > res;
  std::string elem;
  for (std::string::iterator i = in.begin(); i < in.end(); ++i) {
    if (*i == ' ') {
      res.push(elem);
      elem = "";
    } else {
      elem.push_back(*i);
    }
  }
  if (!elem.empty()) {
    res.push(elem);
  }
  return res;
}

long long mod(long long a, long long b)
{
  return (a > 0) == (b > 0) ? a - b * (a / b) : a - b * (a / b - 1);
}

bool isOverflow(long long a, long long b, char op)
{
  if (op == '+' && a > 0 && b > 0) {
    return std::numeric_limits< long long >::max() - a < b;
  }
  if (op == '-' && a < 0 && b < 0) {
    return a - std::numeric_limits< long long >::min() < b;
  }
  if (op == '*') {
    return std::abs(std::numeric_limits< long long >::max()) / a < std::abs(b);
  }
  return false;
}

long long calcBinary(long long a, long long b, char op)
{
  if (isOverflow(a, b, op)) {
    throw std::overflow_error("Overflow");
  }
  if (op == '+') {
    return a + b;
  }
  if (op == '-') {
    return a - b;
  }
  if (op == '*') {
    return a * b;
  }
  if (op == '/') {
    return a / b;
  }
  return mod(a, b);
}

long long computeString(std::string& str)
{
  Queue< std::string > queue;

  Queue< std::string > input = split(str);
  if (getPostfix(input, queue)) {
    return 1;
  }
  Stack< long long > stack;

  while (!queue.isEmpty()) {
    std::string chr = queue.drop();
    if (isNumber(chr)) {
      stack.push(std::stoll(chr));
    } else if (isOperation(chr)) {
      long long b = stack.drop();
      long long a = stack.drop();
      stack.push(calcBinary(a, b, chr[0]));
    } else {
      throw std::logic_error("Incorrect expression");
    }
  }
  long long res = 0;
  if (!stack.isEmpty()) {
    res = stack.drop();
    if (!stack.isEmpty()) {
      throw std::logic_error("Incorrect expression");
    }
  } else {
    throw std::logic_error("Incorrect expression");
  }

  return res;
}
