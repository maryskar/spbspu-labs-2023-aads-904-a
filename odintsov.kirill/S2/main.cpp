#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include <StringSplitter.hpp>
#include <outInvalidCommandMsg.hpp>

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
  using NumericDictionary = odintsov::Dictionary< int, std::string >;
  odintsov::Dictionary< std::string, NumericDictionary > dataSetDict;
  while (dictFile.good()) {
    std::string dictLine;
    std::getline(dictFile, dictLine);
    if (dictLine.empty()) {
      continue;
    }
    odintsov::StringSplitter split(dictLine);
    std::string setName;
    try {
      split >> setName;
    } catch (const std::runtime_error& e) {
      std::cerr << e.what() << '\n';
      return 1;
    }
    NumericDictionary dataSet;
    while (!split.empty()) {
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
  while (std::cin.good()) {
    std::string commandLine;
    std::getline(std::cin, commandLine);
    if (!std::cin.good()) {
      break;
    }
    odintsov::StringSplitter split(commandLine);
    std::string commandName;
    try {
      split >> commandName;
      if (commandName == "print") {
        std::string dataSetName;
        split >> dataSetName;
        NumericDictionary dataSet = dataSetDict.at(dataSetName);
        if (dataSet.empty()) {
          std::cout << "<EMPTY>\n";
        } else {
          std::cout << dataSetName;
          for (NumericDictionary::ConstIter i = dataSet.cbegin(); i != dataSet.cend(); ++i) {
            std::cout << ' ' << i->first << ' ' << i->second;
          }
          std::cout << '\n';
        }
      } else if (commandName == "complement") {
        std::string outDataSetName;
        std::string inDataSet1Name;
        std::string inDataSet2Name;
        split >> outDataSetName >> inDataSet1Name >> inDataSet2Name;
        NumericDictionary outDataSet;
        const NumericDictionary& inDataSet1 = dataSetDict.at(inDataSet1Name);
        const NumericDictionary& inDataSet2 = dataSetDict.at(inDataSet2Name);
        NumericDictionary::ConstIter set1Iter = inDataSet1.cbegin();
        NumericDictionary::ConstIter set2Iter = inDataSet2.cbegin();
        NumericDictionary::Iter lastInserted = outDataSet.beforeBegin();
        NumericDictionary::KeyComp comp = inDataSet1.keyComp();
        for (; set1Iter != inDataSet1.cend(); ++set1Iter) {
          while (set2Iter != inDataSet2.cend() && comp(set2Iter->first, set1Iter->first)) {
            lastInserted = outDataSet.insert(lastInserted, *set2Iter).first;
            ++set2Iter;
          }
          if (set2Iter == inDataSet2.cend() || set2Iter->first != set1Iter->first) {
            lastInserted = outDataSet.insert(lastInserted, *set1Iter).first;
          } else {
            ++set2Iter;
          }
        }
        dataSetDict[outDataSetName] = std::move(outDataSet);
      } else if (commandName == "intersect") {
        std::string outDataSetName;
        std::string inDataSet1Name;
        std::string inDataSet2Name;
        split >> outDataSetName >> inDataSet1Name >> inDataSet2Name;
        NumericDictionary outDataSet;
        const NumericDictionary& inDataSet1 = dataSetDict.at(inDataSet1Name);
        const NumericDictionary& inDataSet2 = dataSetDict.at(inDataSet2Name);
        NumericDictionary::ConstIter set1Iter = inDataSet1.cbegin();
        NumericDictionary::ConstIter set2Iter = inDataSet2.cbegin();
        NumericDictionary::Iter lastInserted = outDataSet.beforeBegin();
        NumericDictionary::KeyComp comp = inDataSet1.keyComp();
        for (; set1Iter != inDataSet1.cend(); ++set1Iter) {
          while (set2Iter != inDataSet2.cend() && comp(set2Iter->first, set1Iter->first)) {
            ++set2Iter;
          }
          if (set2Iter == inDataSet2.cend()) {
            break;
          }
          if (set2Iter->first == set1Iter->first) {
            lastInserted = outDataSet.insert(lastInserted, *set1Iter).first;
          }
        }
        dataSetDict[outDataSetName] = std::move(outDataSet);
      } else if (commandName == "union") {
        std::string outDataSetName;
        std::string inDataSet1Name;
        std::string inDataSet2Name;
        split >> outDataSetName >> inDataSet1Name >> inDataSet2Name;
        NumericDictionary outDataSet;
        const NumericDictionary& inDataSet1 = dataSetDict.at(inDataSet1Name);
        const NumericDictionary& inDataSet2 = dataSetDict.at(inDataSet2Name);
        NumericDictionary::ConstIter set1Iter = inDataSet1.cbegin();
        NumericDictionary::ConstIter set2Iter = inDataSet2.cbegin();
        NumericDictionary::Iter lastInserted = outDataSet.beforeBegin();
        for (; set1Iter != inDataSet1.cend(); ++set1Iter) {
          lastInserted = outDataSet.insert(lastInserted, *set1Iter).first;
        }
        lastInserted = outDataSet.beforeBegin();
        for (; set2Iter != inDataSet2.cend(); ++set2Iter) {
          lastInserted = outDataSet.insert(lastInserted, *set2Iter).first;
        }
        dataSetDict[outDataSetName] = std::move(outDataSet);
      } else {
        throw std::logic_error("Unknown command");
      }
    } catch (const std::logic_error&) {
      odintsov::outInvalidCommandMsg(std::cout) << '\n';
      continue;
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';
      return 2;
    }
  }
}
