#include <iostream>
#include <fstream>
#include <stdexcept>
#include "dictionary.h"
#include "dict_command.h"
#include "read_dict.h"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "invalid number of args\n";
    return 2;
  }
  std::ifstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "file open error\n";
    return 2;
  }

  using dictionary = kryuchkova::Dictionary< int, std::string, std::less< > >;
  using dict_of_dict = kryuchkova::Dictionary< std::string, dictionary, std::less< > >;
  using dict_of_dict_elem = std::pair< std::string, dictionary >;


  dict_of_dict container = kryuchkova::readDictOfDict(in);
  while (std::cin)
  {
    try
    {
      std::string command;
      std::cin >> command;
      if (!std::cin)
      {
        break;
      }
      if (command == "print")
      {
        std::string name;
        std::cin >> name;
        kryuchkova::print(dict_of_dict_elem(name, container.at(name)), std::cout);
      }
      else
      {
        std::string firstName;
        std::string secondName;
        std::string thirdName;
        std::cin >> thirdName >> firstName >> secondName;
        dictionary firstDict = container.at(firstName);
        dictionary secondDict = container.at(secondName);
        dictionary thirdDict;
        if (command == "intersect")
        {
          thirdDict = kryuchkova::make_intersection(firstDict, secondDict);
          container[thirdName] = thirdDict;
        }
        else if (command == "complement")
        {
          thirdDict = kryuchkova::make_comp(firstDict, secondDict);
          container[thirdName] = thirdDict;
        }
        else if (command == "union")
        {
          thirdDict = kryuchkova::make_union(firstDict, secondDict);
          container[thirdName] = thirdDict;
        }
        else
        {
          kryuchkova::OutInvalidCommand(std::cout);
          continue;
        }
      }
    }
    catch (const std::logic_error & e)
    {
      kryuchkova::OutInvalidCommand(std::cout);
      std::cout << '\n';
      continue;
    }
    catch (const std::runtime_error & e)
    {
      break;
    }
  }
  return 0;
}
