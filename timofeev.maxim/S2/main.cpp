#include <iostream>
#include <fstream>
#include <limits>
#include "Dictionary.h"
#include "commandSet.h"
#include "ForwardList.h"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Error\n";
    return 1;
  }
  std::ifstream inFile;
  if (argc == 2)
  {
    inFile.open(argv[1]);
    if (!inFile.is_open())
    {
      std::cerr << "File error" << "\n";
      return 1;
    }
  }

  constexpr auto maxSize = std::numeric_limits< std::streamsize >::max();
  while (!inFile.eof())
  {

    if (inFile.fail())
    {
      inFile.clear();
      inFile.ignore(maxSize, '\n');
    }
  }
  timofeev::Dictionary< std::string, void (*)(std::istream&,) > commands;
  std::string firstPart;
  timofeev::cmdSet(commands);
  while (!std::cin.eof())
  {
    try
    {
      std::cin >> firstPart;
      if (commands.contains(firstPart))
      {
        commands[firstPart](std::cin, )
      }
      else
      {
        commands[firstPart](std::cin, );
      }
    }
    catch (std::logic_error &e)
    {
      timofeev::printError(std::cout);
      std::cin.ignore(maxSize, '\n');
    }
    catch (const std::runtime_error & e)
    {
      break;
    }
  }
  if (std::cin.fail())
  {
    std::cin.clear();
    std::cin.ignore(maxSize, '\n');
  }
  return 0;
}
