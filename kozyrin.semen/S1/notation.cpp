#include "notation.h"
#include <string>

bool isNumber(std::string& str)
{
  for (std::string::iterator i = str.begin(); i < str.end(); ++i) {
    if (!std::isdigit(*i)) {
      return false;
    }
  }
  return true;
}

bool isLowPriority(const std::string& a)
{
  return a == "-" || a == "+";
}

bool isHighPriority(const std::string& a)
{
  return a == "*" || a == "/" || a == "%";
}

bool isLowerPriority(const std::string& a, const std::string& b)
{
  return isLowPriority(a) && isHighPriority(b);
}

bool isOperation(const std::string& chr)
{
  return chr == "+" || chr == "-" || chr == "/" || chr == "*" || chr == "%";
}

int getPostfix(Queue< std::string >& input, Queue< std::string >& queue)
{
  Stack< std::string > stack;
  std::string chr = " ";

  while (!input.isEmpty()) {
    chr = input.drop();

    if (chr == "(") {
      stack.push(chr);
    } else if (chr == ")") {
      bool err = true;
      while (!stack.isEmpty()) {
        std::string top = stack.drop();
        if (top == "(") {
          err = false;
          break;
        }
        queue.push(top);
      }
      if (err) {
        throw std::logic_error("Non-matching brackets");
      }
    } else if (isOperation(chr)){
      while (!stack.isEmpty()) {
        std::string top = stack.drop();
        if (top != "(" && !isLowerPriority(top, chr)) {
          queue.push(top);
        } else {
          stack.push(top);
          break;
        }
      }
      stack.push(chr);
    } else {
      queue.push(chr);
    }
  }
  while (!stack.isEmpty()) {
    queue.push(stack.drop());
  }
  return 0;
}
