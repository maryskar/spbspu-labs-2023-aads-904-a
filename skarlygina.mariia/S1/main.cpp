#include <iostream>
#include <cstring>
#include <fstream>

int main(int argc, char* argv[])
{
  if (argc!=2)
  {
    std::cerr << "Error while reading name of file";
    return 1;
  }

  std::ifstream fin(argv[1]);
  if (!fin.is_open())
  {
    std::cerr << "Reading File could not be opened\n";
    return 1;
  }

}
