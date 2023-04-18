#include "notation.h"
#include <string>
#include "operations.h"

using namespace bowlstalls;

void getPostfix(Queue< std::string >& src, Queue< std::string >& dest)
{
  Stack< std::string > stack;
  std::string chr = " ";

  while (!src.isEmpty()) {
    chr = src.drop();

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
        dest.push(top);
      }
      if (err) {
        throw std::logic_error("Non-matching brackets");
      }
    } else if (isOperation(chr)){
      while (!stack.isEmpty()) {
        std::string top = stack.drop();
        if (top != "(" && !isLowerPriority(top, chr)) {
          dest.push(top);
        } else {
          stack.push(top);
          break;
        }
      }
      stack.push(chr);
    } else {
      dest.push(chr);
    }
  }
  while (!stack.isEmpty()) {
    dest.push(stack.drop());
  }
}
