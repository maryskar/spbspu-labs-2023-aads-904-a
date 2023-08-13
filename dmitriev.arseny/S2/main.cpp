#include <iostream>
#include <fstream>
#include "forwardList.h"
#include "dictionary.h"
#include "dictionaryOfdictionary.h"

int main(int argc, char** argv)
{
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

  dmitriev::DictionaryOfDictionary< int, std::string > dd(file);

  dd.doTheTasksFromInp(std::cin, std::cout);

  return 0;
}
