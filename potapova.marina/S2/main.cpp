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
  Dictionary< long long, std::string, compareFunc > dict;
  std::string in_dict;
  try
  {
    inputDict(*in_ptr, dict, in_dict);
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  return 0;
}
