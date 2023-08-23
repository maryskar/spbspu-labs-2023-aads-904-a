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
  std::string testCompl = "complement";
  std::string testInter = "intersect";
  std::string testUnion = "union";

  comands.insert({testCompl, dmitriev::complementDataset});
  comands.insert({testInter, dmitriev::intersectDataset});
  comands.insert({testUnion, dmitriev::unionDataset});


  dmitriev::Dictionary< std::string, constComand > constComands;
  std::string testPrint = "print";

  constComands.insert({testPrint, dmitriev::printDataset});

  dataset dicOfdic;
  std::string line = "";
  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string datasetName = "";
    ss >> datasetName;

    dicVal datasetDic;

    int key = 0;
    std::string value = "";
    while (ss >> key >> value)
    {
      datasetDic.insert({key, value});
    }

    dicOfdic.insert({datasetName, datasetDic});
  }


  std::string cmdName = "";
  try
  {
    while (std::cin >> cmdName)
    {
      if (!comands.isEmpty(comands.find(cmdName)))
      {
        auto cmd = comands[cmdName];
        cmd(dicOfdic, std::cin);
      }
      else if (!constComands.isEmpty(constComands.find(cmdName)))
      {
        auto constCmd = constComands[cmdName];
        constCmd(dicOfdic, std::cin, std::cout);
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
