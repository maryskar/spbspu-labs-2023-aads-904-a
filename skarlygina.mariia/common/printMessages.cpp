#ifndef PRINT_MESSAGES_H
#define PRINT_MESSAGES_H

#include <iosfwd>
namespace skarlygina
{
  std::ostream& printEmpty(std::ostream&);
  std::ostream& printNoFileToRead(std::ostream&);
  std::ostream& printUnableToReadFile(std::ostream&);
  std::ostream& printInvalidCommand(std::ostream&);
  std::ostream& printBadNumberOfArgs(std::ostream&);
}

#endif

