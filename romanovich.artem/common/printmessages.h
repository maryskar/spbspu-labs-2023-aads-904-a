#ifndef PRINTMESSAGES_H
#define PRINTMESSAGES_H
#include <ostream>
namespace romanovich
{
  std::ostream &printInvalidCommand(std::ostream &out);
  std::ostream &printEmpty(std::ostream &out);
}
#endif
