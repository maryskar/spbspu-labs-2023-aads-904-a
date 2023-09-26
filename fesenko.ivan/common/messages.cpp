#include "messages.h"

void fesenko::outInvalidCommandMessage(std::ostream &out)
{
  out << "<INVALID COMMAND>";
}

void fesenko::outEmptyMessage(std::ostream &out)
{
  out << "<EMPTY>";
}
