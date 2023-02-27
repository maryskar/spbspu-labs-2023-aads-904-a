#include <iostream>
#include <functional>
#include <fstream>
#include "dictionary.h"
#include "forwardlist.h"
int main(int argc, char *argv[])
{
  namespace dsk = dimkashelk;
  if (argc != 2)
  {
    std::cerr << "No filename";
    return 1;
  }
  dsk::ForwardList< dimkashelk::Dictionary< int, std::string, std::less< > > > list;
  std::ifstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "File not open";
    return 1;
  }
  while (in)
  {
    std::string dict_name = "";
    in >> dict_name;
    if (!in)
    {
      std::cerr << "Check file";
      return 1;
    }
    dsk::Dictionary< int, std::string, std::less< > > dict(std::less< int >);
    int key = 0;
    std::string value = "";
    while (in)
    {
      in >> key >> value;
    }
  }
}
