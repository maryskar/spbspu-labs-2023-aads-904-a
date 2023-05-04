#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include <StringSplitter.hpp>

#include "Dictionary.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Invalid amount of arguments\n";
    return 1;
  }
  std::ifstream dictFile(argv[1]);
  if (!dictFile.is_open()) {
    std::cerr << "Dataset could not be opened\n";
    return 1;
  }
  odintsov::Dictionary< std::string, odintsov::Dictionary< int, std::string > > dataSetDict;
  while (dictFile.good()) {
    std::string dictLine;
    std::getline(dictFile, dictLine);
    odintsov::StringSplitter split(dictLine);
    std::string setName;
    try {
      split >> setName;
    } catch (const std::runtime_error& e) {
      std::cerr << e.what() << '\n';
      return 1;
    }
    odintsov::Dictionary< int, std::string > dataSet;
    if (!split.empty()) {
      int key = 0;
      try {
        {
          std::string keyString;
          split >> keyString;
          key = std::stoi(keyString);
        }
        std::string val;
        split >> val;
        dataSet.insert(std::move(key), std::move(val));
      } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
      }
    }
    dataSetDict.insert(std::move(setName), std::move(dataSet));
  }
}
