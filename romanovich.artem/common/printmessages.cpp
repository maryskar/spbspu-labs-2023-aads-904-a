#include "printmessages.h"
std::ostream &romanovich::printInvalidCommand(std::ostream &out)
{
  return out << "<INVALID COMMAND>";
}
std::ostream &romanovich::printEmpty(std::ostream &out)
{
  return out << "<EMPTY>";
}
