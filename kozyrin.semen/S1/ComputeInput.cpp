#include "ComputeInput.h"

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
  res.push(elem);
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

int compute(std::istream& inStream, std::ostream& outStream, std::ostream& errStream)
{
  Stack< int > res = Stack< int >();
  Queue< std::string > queue = Queue< std::string >();
  std::string str;

  while (!inStream.eof()) {
    std::getline(inStream, str);
    if (str.empty()) {
      continue;
    }
    Queue< std::string > input = split(str);
    if (getPostfix(queue, input, errStream)) {
      return 1;
    }
    Stack< int > stack = Stack< int >();

    while (!queue.isEmpty()) {
      std::string chr = queue.drop();
      if (isNumber(chr)) {
        stack.push(stoi(chr));
      } else if (isOperation(chr)) {
        try {
          int b = stack.drop();
          int a = stack.drop();
          stack.push(calcBinary(a, b, chr));
        }
        catch (const std::exception& err) {
          errStream << "Error: " << err.what();
        }
      } else {
        errStream << "Error: Incorrect expression";
        return 3;
      }
    }
    if (!stack.isEmpty()) {
      res.push(stack.drop());
      if (!stack.isEmpty()) {
        errStream << "Error: Incorrect expression";
        return 3;
      }
    } else {
      errStream << "Error: Incorrect expression";
      return 3;
    }
  }
  while (!res.isEmpty()) {
    outStream << res.drop() << ' ';
  }
  return 0;
}