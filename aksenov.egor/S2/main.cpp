#include <iostream>
#include <fstream>
#include "Dictionary.h"
#include "commands.h"
#include <string>

int main(int argc, char* argv[])
{
  using dictionary = aksenov::Dictionary< int, std::string >;
  aksenov::Dictionary< std::string, dictionary > dictionaries;
  if (argc != 2)
  {
    std::cerr << "error" << "\n";
    return 1;
  }
  std::ifstream inputFile(argv[1]);
  if (!inputFile.is_open())
  {
    std::cerr << "Cannot open file: " << "\n";
    return 1;
  }
  aksenov::Dictionary< std::string, void (*)(const std::string &, const std::string &, const std::string &) > commands;
  aksenov::createCommandMap(commands);
  std::string line;
  while (getline(inputFile, line))
  {
    if (line.empty()) {
      continue;
    }

    std::string dataset;
    size_t pos = line.find(' ');
    if (pos != std::string::npos)
    {
      dataset = line.substr(0, pos);
      line = line.substr(pos + 1);
    }

    dictionary dict;
    while (!line.empty())
    {
      pos = line.find(' ');
      int key = stoi(line.substr(0, pos));
      line = line.substr(pos + 1);

      pos = line.find(' ');
      std::string value = line.substr(0, pos);
      line = line.substr(pos + 1);

      dict[key] = value;
    }

    dictionaries[dataset] = dict;
  }

  inputFile.close();
  while (true)
  {
    std::string command = "";
    std::cin >> command;

    if (commands.find(command) != commands.end())
    {
      std::string newDataset = "";
      std::string dataset1 = "";
      std::string dataset2 = "";
      std::cin >> newDataset >> dataset1 >> dataset2;
      commands[command](newDataset, dataset1, dataset2);
    }
    else if (command == "print")
    {
      std::string dataset = "";
      std::cin >> dataset;
      aksenov::printDictionary(dataset, std::cout);
    }
    else {
      std::cout << "<INVALID COMMAND>" << "\n";
    }
    if (std::cin.eof()) {
      break;
    }
  }

  return 0;
}
