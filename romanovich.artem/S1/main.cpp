#include <iostream>
#include <fstream>
#include "stack.h"
template < typename T >
void Stack< T >::push(const T &value)
{
}
template < typename T >
T Stack< T >::pop()
{
}
int main(int argc, char **argv)
{
  if ((argc != 1) && (argc != 2))
  {
    std::cerr << "Not appropriate parameters number.\n";
    return 1;
  }
  Stack< std::string > stack = Stack< std::string >();
  if (argc == 2)
  {
    std::string fileIn = argv[1];
    std::fstream fileInput(fileIn);
    if (!fileInput.is_open())
    {
      std::cerr << "Error while opening file " << fileIn << ".\n";
      return 1;
    }
    for (std::string line; std::getline(fileInput, line);)
    {
      std::cout << line << "\n";
      stack.push(line);
    }
  }
  else
  {
    for (std::string line; std::getline(std::cin, line);)
    {
      std::cout << line << "\n";
      stack.push(line);
    }
  }
  return 0;
}
