#include "commands.h"
#include <iostream>
#include <stdexcept>

namespace chulkov {
  std::string MESSAGE = "Unknown dictionary";

  std::ostream& printEmptyCommand(std::ostream& out)
  {
    return out << "<EMPTY>" << std::endl;
  }

}
