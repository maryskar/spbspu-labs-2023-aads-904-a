#include "isoperator.h"

bool isOperator(std::string c) {
  return (c == "+" || c == "-" || c == "*" || c == "/" || c == "%");
}
