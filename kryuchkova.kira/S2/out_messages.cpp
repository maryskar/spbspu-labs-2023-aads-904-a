#include "out_messages.h"

void kryuchkova::OutInvalidCommand(std::ostream & out)
{
  out << "<INVALID COMMAND>";
}

void kryuchkova::outEmpty(std::ostream & out)
{
  out << "<EMPTY>";
}