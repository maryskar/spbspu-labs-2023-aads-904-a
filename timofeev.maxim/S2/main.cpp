#include <iostream>
#include <fstream>
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
  dictOfDicts dict;
  dict = timofeev::inDict(inFile, dict);
  timofeev::Dictionary< std::string, void (*)(std::istream&, dictOfDicts&) > commands;
  commands = timofeev::cmdSet();
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
        timofeev::Print(std::cin, dict, std::cout);
      }
      else
      {
        commands.at(firstPart)(std::cin, dict);
      }
    }
    catch (const std::invalid_argument &e)
    {
      errors::printInvalid(std::cout);
      break;
    }
    catch (const std::out_of_range &e)
    {
      errors::printEmpty(std::cout);
      break;
    }
  }
  return 0;
}
