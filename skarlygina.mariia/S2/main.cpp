#include <iostream>
#include <fstream>

namespace skarlygina
{
  std::ostream& printInvalidCommand(std::ostream& out)
  {
    return out << "<INVALID COMMAND>\n";
  };
}

int main(int argc, char* argv[])
{
  if (argc == 1)
  {
    std::cerr << "Error arguments\n";
    return 1;
  }
  std::ifstream ifile(argv[1]);
  if (!ifile.is_open())
  {
    std::cerr << "Could not read the file\n";
    return 1;
  }
  skarlygina::printInvalidCommand(std::cout);
}
