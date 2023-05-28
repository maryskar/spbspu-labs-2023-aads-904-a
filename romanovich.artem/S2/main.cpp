#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//
#include <iostream>
#include <forward_list>
#include "forwardlist.h"
//
void doTest();
std::vector< std::string > splitString(const std::string &line, char del)
{
  std::vector< std::string > elems;
  std::string word;
  size_t startPos = 0;
  size_t endPos = line.find(del);
  while (endPos != std::string::npos)
  {
    word = line.substr(startPos, endPos - startPos);
    elems.push_back(word);
    startPos = endPos + 1;
    endPos = line.find(del, startPos);
  }
  word = line.substr(startPos, endPos);
  elems.push_back(word);
  return elems;
}
int main(int argc, char *argv[])
{
  doTest();
  /*if (argc != 2)
  {
    std::cerr << "No file provided.\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Cannot open file.\n";
    return 1;
  }
  std::string line;
  while (std::getline(input, line))
  {
    std::vector< std::string > lineWords = splitString(line, ' ');
    std::string dictName = lineWords[0];
    for (size_t i = 1; i < lineWords.size(); i += 2)
    {
      int key = std::stoi(lineWords[i]);
      std::string val = lineWords[i + 1];
      std::cout << key << " " << val << "\n";
    }
    *//*Dictionary< int, std::string > dictionary{};
    for (size_t i = 2; i < argc; i += 2)
    {
      int key = std::stoi(argv[i]);
      std::string value = argv[i + 1];
      //dictionary.insert(key, value);
      std::cout << key << " " << value << "\n";
    }*//*
  }*/
}
void doTest()
{
  std::forward_list< int > myList1;
  ForwardList< int > myList;
  myList.push_front(3);
  myList.push_front(2);
  myList.push_front(1);
  for (const auto &item: myList)
  {
    std::cout << item << " ";
  }
}
