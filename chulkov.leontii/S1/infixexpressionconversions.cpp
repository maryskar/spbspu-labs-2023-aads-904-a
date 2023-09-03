#include "infixexpressionconversions.h"

#include "isoperator.h"
#include "queue.h"
#include "stack.h"

namespace chulkov {
  int getPriority(std::string c)
  {
    if (c == "+" || c == "-") {
      return 1;
    } else if (c == "*" || c == "/" || c == "%") {
      return 2;
    }
    return 0;
  }

  chulkov::Queue< std::string > infixToPostfix(std::string& infix)
  {
    Queue< std::string > post;
    Stack< std::string > oper;
    std::string str;

    for (char c : infix) {
      if (c == ' ') {
        continue;
      }
      if (std::isdigit(c)) {
        str.push_back(c);
        continue;
      } else if (isOperator(std::string(1, c))) {
        if (!str.empty()) {
          post.push(str);
          str.clear();
        }
        while (!oper.empty() && oper.top() != "(" && getPriority(oper.top()) >= getPriority(std::string(1, c))) {
          post.push(oper.top());
          oper.drop();
        }
        oper.push(std::string(1, c));
      } else if (c == '(') {
        if (!str.empty()) {
          post.push(str);
          str.clear();
        }
        oper.push(std::string(1, c));
      } else if (c == ')') {
        if (!str.empty()) {
          post.push(str);
          str.clear();
        }
        while (!oper.empty() && oper.top() != "(") {
          post.push(oper.top());
          oper.drop();
        }
        if (!oper.empty() && oper.top() == "(") {
          oper.drop();
        } else {
          throw std::runtime_error("bruh, Error in expression");
        }
      } else {
        throw std::runtime_error("yo, Error in expression");
      }
    }
    if (!str.empty()) {
      post.push(str);
      str.clear();
    }
    while (!oper.empty()) {
      if (oper.top() == "(") {
        throw std::runtime_error("Error in expression.");
      }
      post.push(oper.top());
      oper.drop();
    }
    return post;
  }
}
