#include <iostream>
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
  using dictionary = dmitriev::AVL< int, std::string >;
  using dataset = dmitriev::AVL< std::string, dictionary >;
  using iterator = typename dictionary::constIterator;
  using comands = dmitriev::AVL< std::string, void (*)(dataset&, std::string, std::string, std::string) >;
  using constComands = dmitriev::AVL< std::string, void (*)(iterator, iterator, std::string, std::ostream&) >;


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


  comands cmds;
  cmds["complement"] = dmitriev::complementDataset;
  cmds["intersect"] = dmitriev::intersectDataset;
  cmds["union"] = dmitriev::unionDataset;


  constComands constCmds;
  constCmds["print"] = dmitriev::printDataset< iterator >;


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

      if (!cmds.isEmpty(cmds.find(cmdName)))
      {
        std::string newName = makeSubStr(line);
        std::string lhsName = makeSubStr(line);
        std::string rhsName = makeSubStr(line);

        cmds[cmdName](dataSet, newName, lhsName, rhsName);
      }
      else if (!constCmds.isEmpty(constCmds.find(cmdName)))
      {
        std::string name = makeSubStr(line);

        if (dataSet.at(name).isEmpty())
        {
          std::cout << dmitriev::outOfEmptyDataMsg << '\n';
          continue;
        }

        constCmds[cmdName](dataSet.at(name).constBegin(), dataSet.at(name).constEnd(), name, std::cout);

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
