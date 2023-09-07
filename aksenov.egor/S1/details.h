#ifndef ISNUMERIC_H
#define ISNUMERIC_H
#include <string>
#include <iostream>
#include "stack.h"
namespace aksenov
{
  bool isNumeric(std::string const &str);
  bool isOperator(std::string oper);
  int getPriority(std::string operation);
  bool isWhiteSpaceOrEmpty(const std::string &str);
  void processInput(std::istream &in, Stack< long long > &res);
  void out(std::ostream &out, Stack< long long > &result);
}
#endif
