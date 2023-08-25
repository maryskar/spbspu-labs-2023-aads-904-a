#include "computestr.h"
#include <limits>
#include "operations.h"

using namespace bowlstalls;

Queue< std::string > split(const std::string& in)
{
  Queue< std::string > res;
  size_t lb = 0;
  size_t rb = 0;
  size_t len = in.length();
  while (rb < len) {
    rb = in.find(' ', lb);
    res.push(in.substr(lb, rb - lb));
    lb = rb + 1;
  }
  return res;
}

long long mod(long long a, long long b)
{
  return (a > 0) == (b > 0) ? a - b * (a / b) : a - b * (a / b - 1);
}

bool addOverflow(long long a, long long b)
{
  if (a / b >= 0) {
    return std::numeric_limits< long long >::max() - std::abs(a) < std::abs(b);
  }
  return false;
}

bool subOverflow(long long a, long long b)
{
  if (a / b < 0) {
    return std::numeric_limits< long long >::min() + std::abs(a) > -std::abs(b);
  }
  return false;
}

bool multOverflow(long long a, long long b)
{
  return std::abs(std::numeric_limits< long long >::max() / a) < std::abs(b);
}

long long calcBinary(long long a, long long b, char op)
{
  if (op == '+') {
    if (addOverflow(a, b)){
      throw std::overflow_error("Overflow");
    }
    return a + b;
  }
  if (op == '-') {
    if (subOverflow(a, b)){
      throw std::overflow_error("Overflow");
    }
    return a - b;
  }
  if (op == '*') {
    if (multOverflow(a, b)){
      throw std::overflow_error("Overflow");
    }
    return a * b;
  }
  if (op == '/') {
    return a / b;
  }
  if (op == '%') {
    return mod(a, b);
  }
  throw std::logic_error("Incorrect operator");
}

long long bowlstalls::computeString(const std::string& str)
{
  Queue< std::string > input = split(str);
  Queue< std::string > queue = getPostfix(input);
  Stack< long long > stack;

  while (!queue.isEmpty()) {
    std::string chr = queue.drop();
    if (isOperation(chr)) {
      long long b = stack.drop();
      long long a = stack.drop();
      stack.push(calcBinary(a, b, chr[0]));
    } else {
      stack.push(std::stoll(chr));
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
