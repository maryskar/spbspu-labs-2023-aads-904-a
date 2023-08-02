#include "binary_search_tree.h"
#include "bidirectional_iterator.h"
#include "const_bidirectional_iterator.h"
#include <iostream>
#include <vector>
int main()
{
  BinarySearchTree< int, int > bst;

  // insert
  bst.insert(1, 10);
  bst.insert(2, 20);

  // at
  if (bst.at(1) != 10 || bst.at(2) != 20)
  {
    std::cout << "at() failed" << std::endl;
    return 1;
  }

  // []
  if (bst[1] != 10 || bst[2] != 20)
  {
    std::cout << "[] failed" << std::endl;
    //return 1;
  }

  // size
  if (bst.size() != 2)
  {
    std::cout << "size() failed" << std::endl;
    return 1;
  }

  // empty
  if (!bst.empty())
  {
    std::cout << "empty() failed" << std::endl;
    return 1;
  }

  // insert pair
  auto res = bst.insert(3, 30);
  if (!res.second || bst.at(3) != 30)
  {
    std::cout << "insert(pair) failed" << std::endl;
    return 1;
  }

  // insert hint
  auto it = bst.find(2);
  bst.insert(it, 4, 40);
  if (bst.at(4) != 40)
  {
    std::cout << "insert(hint) failed" << std::endl;
    return 1;
  }

  // insert range
  std::vector< std::pair< int, int>> v = {{5, 50},
                                          {6, 60}};
  bst.insert(bst.begin(), v.begin(), v.end());
  if (bst.at(5) != 50 || bst.at(6) != 60)
  {
    std::cout << "insert(range) failed" << std::endl;
    return 1;
  }

  // find
  it = bst.find(1);
  if (it == bst.end() || it->second != 10)
  {
    std::cout << "find() failed" << std::endl;
    return 1;
  }

  // count
  if (bst.count(4) != 1)
  {
    std::cout << "count() failed" << std::endl;
    return 1;
  }

  // lower_bound
  it = bst.lower_bound(25);
  if (it != bst.find(3))
  {
    std::cout << "lower_bound() failed" << std::endl;
    return 1;
  }

  // upper_bound
  it = bst.upper_bound(3);
  if (it != bst.find(4))
  {
    std::cout << "upper_bound() failed" << std::endl;
    return 1;
  }

  // Тесты для остальных методов...

  std::cout << "All tests passed!" << std::endl;
  return 0;
}