#include <iostream>
#include <fstream>
#include <limits>
#include "Dictionary.h"
#include "commandSet.h"
#include "Errors.h"
int main(int argc, char **argv)
//int main()
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

  using dictionary = timofeev::Dictionary< size_t, std::string >;
  using dictOfDicts = timofeev::Dictionary< std::string, dictionary >;
  constexpr auto maxSize = std::numeric_limits< std::streamsize >::max();
  dictOfDicts dict;
  /*while (std::cin)
  {
    std::string name = "";
    std::cin >> name;
    if (name == "stop")
    {
      break;
    }
    size_t key = 0;
    std::string value;
    dictionary dict_t;
    while (std::cin >> key >> value)
    {
      dict_t.insert(std::make_pair(key, value));
    }
    dict[name] = dict_t;
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(maxSize, '\n');
    }
  }*/
  while (!inFile.eof())
  {
    std::string name = "";
    inFile >> name;
    size_t key;
    std::string value;
    dictionary dict_t;
    while (inFile >> key >> value)
    {
      dict_t.insert(std::make_pair(key, value));
    }
    auto tmp = std::make_pair(name, dict_t);
    dict.insert(tmp);
    if (inFile.fail())
    {
      inFile.clear();
      inFile.ignore(maxSize, '\n');
    }
  }
  timofeev::Dictionary< std::string, void (*)(std::istream&, dictOfDicts&) > commands;
  commands = timofeev::cmdSet(commands);
  std::string firstPart;
  while (!std::cin.eof())
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
    catch (const std::logic_error &e)
    {
      errors::printInvalid(std::cout);
      std::cin.ignore(maxSize, '\n');
      break;
    }
    catch (...)
    {
      errors::printError(std::cout);
      std::cin.ignore(maxSize, '\n');
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
