#include "notation.h"

bool isLowPriority(const char a)
{
  return a == '-' || a == '+';
}

bool isHighPriority(const char a)
{
  return a == '*' || a == '/' || a == '%';
}

bool isLowerPriority(const char a, const char b)
{
  return isLowPriority(a) && isHighPriority(b);
}

bool isOperation(const char chr)
{
  return chr == '+' || chr == '-' || chr == '/' || chr == '*' || chr == '%';
}

int getPostfix(Queue< char >& queue, std::istream& inStream, std::ostream& errStream)
{
  Stack< char > stack = Stack< char >();
  char chr = ' ';
  while (!inStream.eof()) {
    inStream >> chr;

    if (chr == '\n') {
      break;
    }
    if (chr == '(') {
      stack.push(chr);
    } else if (chr == ')') {
      bool err = true;
      while (!stack.isEmpty()) {
        char top = stack.drop();
        if (top == '(') {
          err = false;
          break;
        }
        queue.push(top);
      }
      if (err) {
        errStream << "Error: non-matching brackets";
        return 1;
      }
    } else if (std::isdigit(chr)) {
        queue.push(chr);
    } else if (!isOperation(chr)) {
      errStream << "Error: Incorrect characters";
      return 1;
    } else {
      while (!stack.isEmpty()) {
        char top = stack.drop();
        if (!isLowerPriority(chr, top)) {
          queue.push(top);
        } else {
          stack.push(top);
        }
      }
      stack.push(chr);
    }
  }
  while (!stack.isEmpty()) {
    queue.push(stack.drop());
  }
  return 0;
}