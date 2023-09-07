#include <iostream>
#include <fstream>
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
  using dict_of_dict = kryuchkova::Dictionary< std::string, dictionary, std::less< std::string > >;
  using dict_of_dict_elem = std::pair< std::string, dictionary >;

  try
  {
    dict_of_dict container = kryuchkova::readDictOfDict(in);
  }
  catch(const std::exception & e)
  {
    std::cerr << e.what() << '\n';
  }

  try
  {
    dict_of_dict container = kryuchkova::readDictOfDict(in);
    while (std::cin)
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
        std::cin >> firstName >> secondName >> thirdName;
        dictionary firstDict = container.at(firstName);
        dictionary secondDict = container.at(secondName);
        dictionary thirdDict;
        if (command == "intersect")
        {
          thirdDict = kryuchkova::make_intersection(firstDict, secondDict);
        }
        else if (command == "complement")
        {
          thirdDict = kryuchkova::make_comp(firstDict, secondDict);
        }
        else if (command == "union")
        {
          thirdDict = kryuchkova::make_union(firstDict, secondDict);
        }
        else
        {
          kryuchkova::OutInvalidCommand(std::cout);
          continue;
        }
      }
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  } 

}