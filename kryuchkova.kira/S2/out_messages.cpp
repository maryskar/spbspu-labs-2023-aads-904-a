#include "out_messages.h"

std::ostream & kryuchkova::OutInvalidCommand(std::ostream & out)
{
  return out << "<INVALID COMMAND>";
}

std::ostream & kryuchkova::outEmpty(std::ostream & out)
{
  return out << "<EMPTY>";
}
