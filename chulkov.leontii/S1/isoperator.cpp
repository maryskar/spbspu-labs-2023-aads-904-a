#include "isoperator.h"

namespace chulkov {
  bool isOperator(std::string c)
  {
    return (c == "+" || c == "-" || c == "*" || c == "/" || c == "%");
  }
}
