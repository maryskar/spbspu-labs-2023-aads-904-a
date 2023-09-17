#ifndef MESSAGES_H
#define MESSAGES_H
#include <ostream>
namespace fesenko
{
  void outInvalidCommandMessage(std::ostream &out);
  void outEmptyMessage(std::ostream &out);
}
#endif
