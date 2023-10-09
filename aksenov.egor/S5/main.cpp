#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include "functor.h"
#include "traverses.h"
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
  using tree = aksenov::AVL< long long, std::string, std::less< > >;
  tree res;
  long long key = 0;
  std::string val = "";
  while (inp)
  {
    inp >> key >> val;
    if (!inp)
    {
      break;
    }
    res.insert(key, val);
    inp.clear();
  }
  if (res.isEmpty())
  {
    std::cout << "<EMPTY>" << "\n";
    return 0;
  }
  try
  {
    auto keys = aksenov::makeTraverse< aksenov::keySummator >();
    auto vals = aksenov::makeTraverse< aksenov::stringSummator >();
    aksenov::stringSummator str;
    aksenov::keySummator key;
    std::cout << (res.*keys.at(argv[1]))(key).get();
    std::cout << (res.*vals.at(argv[1]))(str).get() << "\n";
  }
  catch (...)
  {
    std::cout << "<INVALID COMMAND>" << "\n";
    return 1;
  }
}
