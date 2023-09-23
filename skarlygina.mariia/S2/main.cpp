#include <iostream>

namespace skarlygina
{
  std::ostream& printInvalidCommand(std::ostream& out)
  {
    return out << "<INVALID COMMAND>\n";
  };
}

int main()
{
  skarlygina::printInvalidCommand(std::cout);
}
