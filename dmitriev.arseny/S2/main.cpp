#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <functional>

#include "dictionary.h"
#include "commands.h"

int main(int argc, char** argv)
{
  using dicVal = dmitriev::Dictionary< int, std::string >;
  using dataset = dmitriev::Dictionary< std::string, dicVal >;
  using comand = std::function< void(dataset& dicOfDic, std::istream& inp) >;
  using constComand = std::function< void(dataset& dicOfDic, std::istream& inp, std::ostream& out) >;

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


  dataset dicOfDic;
  while (file)
  {
    std::string name;
    file >> name;
    if (!file)
    {
      break;
    }
    dicVal datasetDic;
    std::size_t key = 0;
    std::string value;
    while (file)
    {
      file >> key >> value;
      if (!file)
      {
        break;
      }
      dicVal::fListPair fP = std::make_pair(key, value);
      datasetDic.insert(fP);
    }
    file.clear();
    dicOfDic.insert({name, datasetDic});
  }

  std::string cmdName = "";
  try
  {
    while (std::cin >> cmdName)
    {
      if (!comands.isEmpty(comands.find(cmdName)))
      {
        auto cmd = comands[cmdName];
        cmd(dicOfDic, std::cin);
      }
      else if (!constComands.isEmpty(constComands.find(cmdName)))
      {
        auto constCmd = constComands[cmdName];
        constCmd(dicOfDic, std::cin, std::cout);
        std::cout << '\n';
      }
      else
      {
        std::cout << "<INVALID COMMAND>" << '\n';
      }
    }
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << '\n';
  }

  return 0;
}
