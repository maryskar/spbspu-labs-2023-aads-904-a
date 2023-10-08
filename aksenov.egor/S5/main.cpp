#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <AVL/AVL.h>

int main(int argc, char *argv[])
{
  std::ifstream inp;
  if (argc == 3)
  {
    inp.open(argv[2]);
    if (!inp.is_open())
    {
      std::cerr << "Cannot open file\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "Wrong number of args\n";
    return 1;
  }

  aksenov::AVL< long long, std::string > tree;
  long long key = 0;
  std::string val = "";
  try
  {
    while (inp >> key >> val)
    {
      tree.insert({key, val});
    }
  }
  catch (const std::invalid_argument &e)
  {
    std::cout << "<EMPTY>" << "\n";
  }
  catch (...)
  {
    std::cout << "<INVALID COMMAND>" << "\n";
  }
}
