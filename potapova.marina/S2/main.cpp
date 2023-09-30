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

int main()
{
  using namespace potapova;
  const char* argv[]{"", "C:/Users/79213/Desktop/Marina/UniversitySPBSPU/aip_labs/spbspu-labs-2023-aads-904-a/potapova.marina/S2/in.txt"};
  std::istream* in_ptr = nullptr;
  std::ifstream input_file;
  input_file.open(argv[1]);
  if (!input_file.is_open())
  {
    std::cerr << "Failed to open file\n";
    return 1;
  }
  in_ptr = &input_file;
 
  bool compareFunc(const long long& first, const long long& second);

  Dictionary< long long, std::string, compareFunc > dict1;
  Dictionary< long long, std::string, compareFunc > dict2;
  std::string first, second;

  inputDict< compareFunc >(*in_ptr, dict1, first);
  inputDict< compareFunc >(*in_ptr, dict2, second);



  std::cout << dict1.join(dict2) << '\n';

  return 0;
}
