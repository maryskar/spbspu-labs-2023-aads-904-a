#include "printMessages.h"
#include <iostream>

namespace chulkov
{
  std::ostream& printEmpty(std::ostream& out)
  {
    out << "<EMPTY>" << '\n';
    return out;
  }
  std::ostream& printNoFileToRead(std::ostream& out)
  {
    out << "No file to read" << '\n';
    return out;
  }
  std::ostream& printUnableToReadFile(std::ostream& out)
  {
    out << "Unable to read the file" << '\n';
    return out;
  }
  std::ostream& printInvalidCommand(std::ostream& out)
  {
    out << "<INVALID COMMAND>" << '\n';
    return out;
  }
}
