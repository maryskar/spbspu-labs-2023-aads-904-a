#include "has_higher_precedence.h"
#include <map>
bool hasHigherPrecedence(Stack< std::string >& operator_stack, std::string token)
{
  std::map<std::string, int> precedence;
  precedence["+"] = 1;
  precedence["-"] = 1;
  precedence["*"] = 2;
  precedence["/"] = 2;
  precedence["%"] = 2;
  precedence["("] = 3;
  precedence[")"] = 3;

  std::string top_operator = operator_stack.top();
  return precedence[top_operator] > precedence[token];
}
