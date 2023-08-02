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

  turkin::AVLtree< int, int, std::less< int > > tree;
  auto data = std::make_pair(1, 1);
  auto data2 = std::make_pair(123112, 4);
  auto data3 = std::make_pair(3331, 3);
  auto data4 = std::make_pair(188, 2);

  tree.insert(data4);
  std::cout << "inserted 4\n";
  tree.insert(data);
  std::cout << "inserted 1\n";
  tree.insert(data2);
  std::cout << "inserted 2\n";
  tree.insert(data3);
  std::cout << "inserted 3\n";


  auto it = tree.src();
  it++;
  auto result = it->first;
  std::cout << result << "\n";
  it++;
  result = it->first;
  std::cout << result << "\n";
  it--;
  result = it->first;
  std::cout << result << "\n";
  it--;
  result = it->first;
  std::cout << result << "\n";
  it--;
  result = it->first;
  std::cout << result << "\n";
  return 0;
}
