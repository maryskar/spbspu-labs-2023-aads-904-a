#include "outputOfSpecialMessages.h"

std::ostream& dmitriev::outOfInvalivdComandMsg(std::ostream& out)
{
  return out << "<INVALID COMMAND>";
}

std::ostream& dmitriev::outOfEmptyDataMsg(std::ostream& out)
{
  return out << "<EMPTY>";
}
