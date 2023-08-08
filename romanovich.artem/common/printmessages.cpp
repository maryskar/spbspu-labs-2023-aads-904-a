#include "printmessages.h"
std::ostream &printInvalidCommand(std::ostream &out)
{
  return out << "<INVALID COMMAND>";
}
std::ostream &printEmpty(std::ostream &out)
{
  return out << "<EMPTY>";
}
