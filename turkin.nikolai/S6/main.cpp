#include <deque>
#include <iostream>
#include <string>
#include <cstddef>

#include "qsort.hpp"
#include "shell.hpp"

#include <out-msg.hpp>
#include <vector>

int main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "input error\n";
    return 1;
  }
  
  std::string trvs_t = argv[2];
  std::string data_t = argv[3];
  //std::size_t amount = std::stoull(argv[4]);
  std::deque< int > data = {2, 1, 235, 1234, 74, 2, 324};
  turkin::shell(data.begin(), data.end(), std::less< int >());
  for (auto it: data) std::cout << it << " ";
  std::cout << "\n";
}
