#include "outputOfErrors.h"

void dmitriev::outOfInvalivdComandErr(std::ostream& out)
{
  out << "<INVALID COMMAND>" << '\n';
}

void dmitriev::outOfEmptyDataErr(std::ostream& out)
{
  out << "<EMPTY" << '\n';
}
