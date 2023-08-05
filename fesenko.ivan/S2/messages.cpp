#include "messages.h"

void fesenko::outInvalidCommandMessage(std::ostream &out)
{
  out << "<INVALID COMMAND>\n";
}

void fesenko::outEmptyMessage(std::ostream &out)
{
  out << "<EMPTY>\n";
}
