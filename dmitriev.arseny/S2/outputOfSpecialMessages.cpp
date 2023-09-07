#include "outputOfSpecialMessages.h"

void dmitriev::outOfInvalivdComandMsg(std::ostream& out)
{
  out << "<INVALID COMMAND>";
}

void dmitriev::outOfEmptyDataMsg(std::ostream& out)
{
  out << "<EMPTY>";
}
