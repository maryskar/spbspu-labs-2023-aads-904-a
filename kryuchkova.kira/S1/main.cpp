#include "queue.h"
#include "stack.h"
#include "node.h"
#include <iostream>
#include <fstream>
#include <sstream>


int main(int argc, char *argv[])
{
  if (argc != 1 && argc != 2)
  {
    std::cerr  << "Not correct number of arguments for program\n";
    return 1;
  }
  kryuchkova::Queue < std::string > inf;
  kryuchkova::Queue < std::string > post;
  std::string str;
  long long result = 0;

  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    if (!file)
    {
      std::cerr << "Error with opening file";
      return 1;
    }
    while (!file.eof())
    {
      std::getline(file, str);
      if (str.empty())
      {
        continue;
      }
      try
      {

      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
      std::cout << result << '\n';
    }
  }

  else
  {
    while (std::cin)
    {
      std::getline(std::cin, str);
      if (!std::cin)
      {
        break;
      }
      if (str.empty())
      {
        continue;
      }
      try
      {

      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
      std::cout << result << '\n';
    }
  }
  return 0;
}
