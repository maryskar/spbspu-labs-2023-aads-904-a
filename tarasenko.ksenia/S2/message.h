#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>

namespace tarasenko
{
  std::ostream& outMessageInvalidCommand(std::ostream& out)
  {
    return out << "<INVALID COMMAND>";
  }

  std::ostream& outMessageEmpty(std::ostream& out)
  {
    return out << "<EMPTY>";
  }
}
#endif
