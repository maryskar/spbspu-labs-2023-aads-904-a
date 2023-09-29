#include <iostream>
#include <fstream>
#include "reading_dicts.h"

namespace skarlygina
{
  std::ostream& printInvalidCommand(std::ostream& out)
  {
    return out << "<INVALID COMMAND>\n";
  };
}

int main(int argc, char** argv)
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

  try
  {
    auto data = skarlygina::getDictis(ifile);
    ifile.close();
    std::istream& in = std::cin;

    while (!in.eof())
    {
      try
      {
        auto words = skarlygina::getWords(in, '\n');
        if (words.isEmpty())
        {
          continue;
        }
        if (words.getSize() < 2)
        {
          throw std::invalid_argument("You need more args!\n");
        }

        auto w_iterator = words.cbegin();
        std::string command = *(w_iterator++);
        std::string name = *(w_iterator++);

        if (command == "print")
        {
          skarlygina::print(std::cout, name, data);
          continue;
        }
        if (words.getSize() < 4)
        {
          throw std::invalid_argument("You need less args!\n");
        }
        std::string lhs = *(w_iterator++);
        std::string rhs = *w_iterator;
        skarlygina::readCommand(data, lhs, rhs, command, name);
      }
      catch (const std::invalid_argument&)
      {
        skarlygina::printInvalidCommand(std::cout);
      }
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }
}
