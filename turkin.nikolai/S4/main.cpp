#include <iostream>
#include <cstddef>
#include <string>
#include <functional>
#include "avl-tree/avl-tree.hpp"
#include "out-msg.hpp"


int main(int argc, char * argv[])
{
  if (argc == 1)
  {
    std::cerr << "no file\n";
    return 1;
  }

  std::ifstream file;
  file.open(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "cannot open file\n";
    return 1;
  }

  turkin::AVLtree< int, int, std::greater< int > > tree;
  auto data1 = std::make_pair(1, 1);
  auto data2 = std::make_pair(2, 2);
  auto data3 = std::make_pair(3, 3);
  auto data4 = std::make_pair(4, 4);

  tree.insert(data1); std::cout << "inserted 1\n";
  std::cout << "key: " << tree.root()->first << "\t data: " << tree.root()->second << "\n";
  tree.insert(data2); std::cout << "inserted 2\n";
  std::cout << "key: " << tree.root()->first << "\t data: " << tree.root()->second << "\n";
  tree.insert(data3); std::cout << "inserted 3\n";
  std::cout << "key: " << tree.root()->first << "\t data: " << tree.root()->second << "\n";
  tree.insert(data4); std::cout << "inserted 4\n";

  std::cout << "key: " << tree.begin()->first << "\t data: " << tree.begin()->second << "\n";
  std::cout << "key: " << tree.root()->first << "\t data: " << tree.root()->second << "\n";
  std::cout << "key: " << tree.end()->first << "\t data: " << tree.end()->second << "\n";

  //for (auto it : tree)
  //{
  //  std::cout << "key: " << it.first << "\t data: " << it.second << "\n";
  //}

  return 0;
}
