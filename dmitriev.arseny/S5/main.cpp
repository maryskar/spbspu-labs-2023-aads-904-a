#include <iostream>
#include <fstream>
#include <string>
#include <AVL.h>


int main()
{
  if (argc != 3)
  {
    std::cout << "incorrect argc count" << '\n';
    return 1;
  }
  std::ifstream file (argv[2]);
  if (!file.is_open())
  {
    std::cout << "problems with opening file" << '\n';
    return 1;
  }






  return 0;
}
