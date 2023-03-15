#include <iostream>
#include <fstream>

int main(int argc, char ** argv)
{
  if (argc != 2 && argc != 3)
  {
    std::cerr << "Incorrect arguments\n";
    return 1;
  }
  else if (argc == 3)
  {
    std::ifstream inpFile;
    inpFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try
    {
      inpFile.open(argv[2]);
    }
    catch (const std::exception& ex)
    {
      std::cerr << ex.what() << "\n";
      return 1;
    }
  }
  else
  {

  }
  return 0;
}
