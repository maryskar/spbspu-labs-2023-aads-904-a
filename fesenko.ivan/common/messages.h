#ifndef MESSAGES_H
#define MESSAGES_H
#include <fstream>
namespace fesenko
{
  void outInvalidCommandMessage(std::ostream &out);
  void outEmptyMessage(std::ostream &out);
}
#endif
