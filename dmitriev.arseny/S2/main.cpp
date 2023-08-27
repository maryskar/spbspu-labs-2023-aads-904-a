#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <functional>

#include "datasetCommands.h"

int main(int argc, char** argv)
{
  using dictionary = dmitriev::Dictionary< int, std::string >;
  using dataset = dmitriev::Dictionary< std::string, dictionary >;
  using comand = std::function< void(dataset& dataSet, std::string name, std::string lhsName, std::string rhsName) >;
  using constComand = std::function< void(const dataset& dataSet, std::string name, std::ostream& out) >;

  if (argc != 2)
  {
    std::cout << "no file was found" << '\n';
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cout << "problems while opening file" << '\n';
    return 1;
  }


  dmitriev::Dictionary< std::string, comand > comands;
  comands["complement"] = dmitriev::complementDataset;
  comands["intersect"] = dmitriev::intersectDataset;
  comands["union"] = dmitriev::unionDataset;

  dmitriev::Dictionary< std::string, constComand > constComands;
  constComands["print"] = dmitriev::printDataset;


  dataset dataSet;
  std::string line = "";
  while (std::getline(file, line))
  {
    std::stringstream strStream(line);
    std::string name = "";

    strStream >> name;
    if (!strStream)
    {
      std::cout << "problems while reading file";
      return 1;
    }

    dictionary dict;
    std::size_t key = 0;
    std::string value = "";

    while (strStream >> key >> value)
    {
      dict.insert({key, value});
    }
    dataSet.insert({name, dict});
  }

  while (std::getline(std::cin, line))
  {
    std::stringstream strStream(line);
    std::string cmdName = "";

    try
    {
      strStream >> cmdName;
      if (!strStream)
      {
        throw std::runtime_error("incorrect args");
      }

      if (!comands.isEmpty(comands.find(cmdName)))
      {
        std::string newName = "";
        std::string lhsName = "";
        std::string rhsName = "";
        strStream >> newName >> lhsName >> rhsName;
        if (!strStream)
        {
          throw std::runtime_error("incorrect args");
        }

        auto cmd = comands[cmdName];
        cmd(dataSet, newName, lhsName, rhsName);
      }
      else if(!constComands.isEmpty(constComands.find(cmdName)))
      {
        std::string name = "";
        strStream >> name;
        if (!strStream)
        {
          throw std::runtime_error("incorrect args");
        }

        auto constCmd = constComands[cmdName];
        constCmd(dataSet, name, std::cout);

        std::cout << '\n';
      }
      else
      {
        throw std::runtime_error("incorrect args");
      }
    }
    catch (const std::runtime_error&)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << '\n';
    }
  }

  return 0;
}
