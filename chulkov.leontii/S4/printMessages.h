#ifndef PRINTMESSAGES_H
#define PRINTMESSAGES_H
#include <iosfwd>

namespace chulkov
{
  std::ostream& printEmpty(std::ostream&);
  std::ostream& printNoFileToRead(std::ostream&);
  std::ostream& printUnableToReadFile(std::ostream&);
  std::ostream& printInvalidCommand(std::ostream&);
}

#endif
