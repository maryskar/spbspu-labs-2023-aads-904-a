#include "avl-tree/avl-tree.hpp"
#include "process-sort.hpp"
#include <functional>
#include <iostream>
#include <string>
#include <cstddef>

int main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "input error\n";
    return 1;
  }

  std::string trvs_t = argv[1];
  std::string data_t = argv[2];
  std::size_t amount = std::stoull(argv[3]);
  turkin::AVLtree< std::string, void (*)(std::size_t, std::ostream &), std::less< > > pr;
  pr.insert("ascending ints", process< int, std::less< int > >);
  pr.insert("ascending floats", process< float, std::less< float > >);
  pr.insert("descending ints", process< int, std::greater< int > >);
  pr.insert("descending floats", process< float, std::greater< float > >);

  try
  {
    pr.at(trvs_t + " " + data_t)(amount, std::cout);
  }
  catch (...)
  {
    std::cerr << "bad input\n";
    return 1;
  }
  return 0;
}
