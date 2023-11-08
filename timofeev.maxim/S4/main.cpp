#include <iostream>
#include <fstream>
#include <AVL/AVL.h>
#include <commands/commandSet.h>
#include <Errors.h>
#include <inDict.h>

int main(int argc, char *argv[])
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
  using lilAVl = timofeev::AVL< size_t, std::string, std::less<> >;
  using hugeAVL = timofeev::AVL< std::string, lilAVl, std::less<> >;
  using command = timofeev::AVL< std::string, void (*)(std::istream&, hugeAVL&, lilAVl) >;
  lilAVl lildict;
  hugeAVL dict;
  dict = timofeev::inDict< hugeAVL, lilAVl >(inFile, dict);
  command commands;
  commands = timofeev::cmdSet< command, lilAVl >();
  while (!std::cin.eof())
  {
    try
    {
      std::string firstPart = "";
      std::cin >> firstPart;
      if (!std::cin)
      {
        break;
      }
      if (firstPart == "print")
      {
        timofeev::doPrint< hugeAVL >(std::cin, dict, std::cout);
      }
      else
      {
        commands.at(firstPart)(std::cin, dict, lildict);
      }
    }
    catch (const std::invalid_argument &e)
    {
      timofeev::printInvalid(std::cout);
      std::cout << "\n";
      break;
    }
    catch (const std::out_of_range &e)
    {
      timofeev::printEmpty(std::cout);
      std::cout << "\n";
      break;
    }
  }
  return 0;
}
