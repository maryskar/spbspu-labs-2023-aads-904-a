#include <iostream>
#include <fstream>
#include <limits>
#include "Dictionary.h"
#include "commandSet.h"
#include "Errors.h"
#include "inDict.h"
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
  using dictionary = timofeev::Dictionary< size_t, std::string, std::less<> >;
  using dictOfDicts = timofeev::Dictionary< std::string, dictionary, std::less<> >;
  constexpr auto maxSize = std::numeric_limits< std::streamsize >::max();
  dictOfDicts dict;
  dict = timofeev::inDict(inFile, dict);
  timofeev::Dictionary< std::string, void (*)(std::istream&, dictOfDicts&) > commands;
  commands = timofeev::cmdSet(commands);
  std::string firstPart = "";
  while (std::cin)
  {
    try
    {
      std::cin >> firstPart;
      if (firstPart == "print")
      {
        timofeev::Print(std::cin, dict, std::cout);
      }
      else if (commands.contains(firstPart))
      {
        commands[firstPart](std::cin, dict);
      }
    }
    catch (const std::invalid_argument &e)
    {
      errors::printInvalid(std::cout);
      std::cin.ignore(maxSize, '\n');
    }
    catch (const std::out_of_range &e)
    {
      errors::printEmpty(std::cout);
      std::cin.ignore(maxSize, '\n');
    }
    catch (...)
    {
      errors::printInvalid(std::cout);
      std::cin.ignore(maxSize, '\n');
    }
  }
  if (std::cin.fail())
  {
    std::cin.clear();
    std::cin.ignore(maxSize, '\n');
  }
  return 0;
}
