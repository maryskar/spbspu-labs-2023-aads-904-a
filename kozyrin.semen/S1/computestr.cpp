#include "computestr.h"

Queue< std::string > split(std::string in)
{
  Queue< std::string > res = Queue< std::string >();
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

int calcBinary(int a, int b, const std::string& op)
{
  if (op == "+") {
    return a + b;
  }
  if (op == "-") {
    return a - b;
  }
  if (op == "*") {
    return a * b;
  }
  if (op == "/") {
    return a / b;
  }
  return a % b;
}

int computeString(std::string& str)
{
  Queue< std::string > queue = Queue< std::string >();

  Queue< std::string > input = split(str);
  if (getPostfix(input, queue)) {
    return 1;
  }
  Stack< int > stack = Stack< int >();

  while (!queue.isEmpty()) {
    std::string chr = queue.drop();
    if (isNumber(chr)) {
      stack.push(stoi(chr));
    } else if (isOperation(chr)) {
      int b = stack.drop();
      int a = stack.drop();
      stack.push(calcBinary(a, b, chr));
    } else {
      throw std::logic_error("Incorrect expression");
    }
  }
  int res = 0;
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
