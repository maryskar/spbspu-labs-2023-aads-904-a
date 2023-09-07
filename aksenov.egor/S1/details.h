#ifndef ISNUMERIC_H
#define ISNUMERIC_H
#include <string>
namespace aksenov
{
  bool isNumeric(std::string const &str);
  bool isOperator(std::string oper);
  int getPriority(std::string operation);
}
#endif
