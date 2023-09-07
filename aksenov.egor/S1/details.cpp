#include "details.h"
#include "stack.h"
#include "queue.h"
#include "stringToInfix.h"
#include "convertToPostfix.h"
#include "solvePostfixExpr.h"
bool aksenov::isNumeric(std::string const &str)
{
  char* p = nullptr;
  std::strtol(str.c_str(), &p, 10);
  return *p == 0;
}
bool aksenov::isOperator(std::string oper)
{
  return oper == "+" || oper == "-" || oper == "*" || oper == "/" || oper == "%";
}
int aksenov::getPriority(std::string operation)
{
  if (operation == "+" || operation == "-")
  {
    return 1;
  }
  else if (operation == "*" || operation == "/" || operation == "%")
  {
    return 2;
  }
  else
  {
    return 0;
  }
}
bool aksenov::isWhiteSpaceOrEmpty(const std::string &str)
{
  return str.find_first_not_of(" \n") == std::string::npos;
}

void aksenov::processInput(std::istream &in, aksenov::Stack< long long > &res)
{
  std::string str;
  while (std::getline(in, str))
  {
    if (aksenov::isWhiteSpaceOrEmpty(str))
    {
      continue;
    }
    aksenov::Queue<std::string> infixQueue = aksenov::convertToInfix(str);
    aksenov::Queue<std::string> postfixQueue = aksenov::getPostfixQueue(infixQueue);
    res.push(aksenov::solvePostfixExpr(postfixQueue));
  }
}

void aksenov::out(std::ostream &out, aksenov::Stack< long long > &result)
{
  while (!result.isEmpty())
  {
    out << result.get();
    result.pop();
    if (!result.isEmpty())
    {
      out << " ";
    }
  }
}
