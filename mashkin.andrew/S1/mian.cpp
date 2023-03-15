#include <iostream>
#include <fstream>

int main(int argc, char ** argv)
{
  if (argc != 2 || argc != 3)
  {
    std::cerr << "Incorrect arguments\n";
    return 1;
  }
  return 0;
}
