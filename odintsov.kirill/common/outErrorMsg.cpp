#include "outErrorMsg.hpp"
#include <iostream>

std::ostream& odintsov::outInvalidCommandMsg(std::ostream& out)
{
  return out << "<INVALID COMMAND>";
}

std::ostream& odintsov::outEmptyContainerMsg(std::ostream& out)
{
  return out << "<EMPTY>";
}
