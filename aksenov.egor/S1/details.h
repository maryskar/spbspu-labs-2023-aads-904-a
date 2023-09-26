#ifndef DETAILS_H
#define DETAILS_H
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
  bool isloverOrSamePriority(std::string lhs, std::string rhs);
}
