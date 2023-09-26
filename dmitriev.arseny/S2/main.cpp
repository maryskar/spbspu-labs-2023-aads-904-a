#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <functional>

#include <datasetCommands.h>
#include <outputOfSpecialMessages.h>

std::string makeSubStr(std::string& line)
{
  std::string res = "";
  std::size_t pos = line.find(' ');

  if (pos != std::string::npos)
  {
    res = line.substr(0, pos);
    line.erase(0, pos + 1);

    return res;
  }
  else if (line != "")
  {
    res = line;
    line = "";

    return res;
  }
  else
  {
    throw std::runtime_error("incorrect args");
  }
}

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
  std::string name = "";

  while (std::getline(file, line))
  {
    try
    {
      name = makeSubStr(line);
    }
    catch (const std::exception&)
    {
      continue;
    }

    dictionary dict;
    std::size_t key = 0;
    std::string value = "";

    while (line != "")
    {
      try
      {
        key = std::stoul(makeSubStr(line));
        value = makeSubStr(line);
      }
      catch (const std::exception&)
      {
        std::cout << "problems while reading file" << '\n';
        return 1;
      }

      dict.insert({key, value});
    }
    dataSet.insert({name, dict});
  }

  std::string cmdName = "";
  while (std::getline(std::cin, line))
  {
    try
    {
      cmdName = makeSubStr(line);

      if (!comands.isEmpty(comands.find(cmdName)))
      {
        std::string newName = makeSubStr(line);
        std::string lhsName = makeSubStr(line);
        std::string rhsName = makeSubStr(line);

        auto cmd = comands[cmdName];
        cmd(dataSet, newName, lhsName, rhsName);
      }
      else if (!constComands.isEmpty(constComands.find(cmdName)))
      {
        std::string name = makeSubStr(line);

        auto constCmd = constComands[cmdName];
        constCmd(dataSet, name, std::cout);

        std::cout << '\n';
      }
      else
      {
        throw std::runtime_error("incorrect args");
      }
    }

    catch (const std::exception& e)
    {
      if (typeid(e) == typeid(std::runtime_error) || typeid(e) == typeid(std::out_of_range))
      {
        dmitriev::outOfInvalivdComandMsg(std::cout);
        std::cout << '\n';
      }
      else
      {
        std::cout << e.what() << '\n';
      }
    }
  }

  return 0;
}
