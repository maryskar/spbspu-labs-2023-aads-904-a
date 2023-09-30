#include <iostream>
#include <stdexcept>
#include <fstream>
#include "forwardList.h"
#include "dictionary.h"
#include "workWithIO.h"

bool compareFunc(const long long& first, const long long& second)
{
  return first > second;
}

int main(int argc, char* argv[])
{
  using namespace potapova;
  std::istream* in_ptr = nullptr;
  std::ifstream input_file;
  if (argc > 2)
  {
    std::cerr << "Incorrect number of arguments\n";
    return 1;
  }
  else if (argc == 2)
  {
    input_file.open(argv[1]);
    if (!input_file.is_open())
    {
      std::cerr << "Failed to open file\n";
      return 1;
    }
    in_ptr = &input_file;
  }
  else
  {
    std::cerr << "No file to open\n";
    return 1;
  }
 
  bool compareFunc(const long long& first, const long long& second);

  Dictionary< long long, std::string, compareFunc > dict1;
  Dictionary< long long, std::string, compareFunc > dict2;
  std::string first, second;

  inputDict< compareFunc >(*in_ptr, dict1, first);
  inputDict< compareFunc >(*in_ptr, dict2, second);

  std::cout << dict1;
  std::cout << dict2;

  dict1.complement(dict2);

  std::cout << dict1;

  return 0;
}
