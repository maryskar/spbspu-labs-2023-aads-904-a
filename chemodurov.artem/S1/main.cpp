#include <iostream>

int main(int argc, char ** argv)
{
  if (argc != 1 || argc != 2)
  {
    std::cerr << "Error\n";
    return 1;
  }
  return 0;
}