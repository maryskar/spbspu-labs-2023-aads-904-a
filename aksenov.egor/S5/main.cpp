#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <functional>
#include "functor.h"
#include "traverses.h"
#include <AVL/AVL.h>
#include <getDictFromInput.h>

int main()
{
  /*std::ifstream inp;
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
  auto dict = aksenov::getDictFromInput< tree >(inp);
  if (tree.isEmpty())
  {
    std::cout << "<EMPTY>" << "\n";
    return 0;
  }*/
  std::pair< long long, std::string > pair{4, "four"};
  std::pair< long long, std::string > pair2{5, "five"};
  std::pair< long long, std::string > pair3{6, "six"};
  std::pair< long long, std::string > pair4{7, "seven"};
  aksenov::keySummator ksummator;
  aksenov::stringSummator strSummator;
  try
  {
    ksummator(pair);
    ksummator(pair2);
    std::cout << ksummator.get() << "\n";
    strSummator(pair);
    strSummator(pair2);
    std::cout << strSummator.get() << "\n";
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
