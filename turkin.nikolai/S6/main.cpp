#include <iostream>
#include <string>
#include <cstddef>

#include <out-msg.hpp>

int main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "input error\n";
    return 1;
  }
  
  std::string trvs_t = argv[2];
  std::string data_t = argv[3];
  std::size_t amount = std::stoull(argv[4]);
  
  try
  {
    
  }
  catch (...)
  {
    turkin::outInvalidCMD(std::cerr);
  }
  std::cout << "hi\n";
}
