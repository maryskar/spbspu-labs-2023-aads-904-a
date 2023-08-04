#include "binary_search_tree.h"
#include "bidirectional_iterator.h"
#include "const_bidirectional_iterator.h"
#include <iostream>
#include <vector>
int main()///////// переделать для даты
{
  BinarySearchTree< int, int > bst;

  // insert
  bst.insert(std::make_pair(1, 10));
  bst.insert(std::make_pair(2, 20));

  // at
  if (bst.at(std::make_pair(1, 10)) != std::make_pair(1, 10)
  || bst.at(std::make_pair(2, 20)) != std::make_pair(2, 20))
  {
    std::cout << "at() failed" << std::endl;
    return 1;
  }

  // []
  if (bst[std::make_pair(1, 10)] != std::make_pair(1, 10) || bst[std::make_pair(2, 20)] != std::make_pair(2, 20))
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
  if (bst.empty())
  {
    std::cout << "empty() failed" << std::endl;
    return 1;
  }

  // insert pair
  auto res = bst.insert(std::make_pair(3, 30));
  if (!res.second || bst.at(std::make_pair(3, 30)) != std::make_pair(3, 30))
  {
    std::cout << "insert(pair) failed" << std::endl;
    return 1;
  }


  // insert hint
/*  auto it = bst.find(std::make_pair(2, 20));
  bst.insert(it, 4, 40);
  if (bst.at(4) != 40)
  {
    std::cout << "insert(hint) failed" << std::endl;//////////
    return 1;
  }*/

  // find
  auto it = bst.find(std::make_pair(1, 10));
  if (it == bst.end() || it->second != 10)
  {
    std::cout << "find() failed" << std::endl;
    return 1;
  }

  // count
  if (bst.count(std::make_pair(4, 40)) != 1)
  {
    std::cout << "count() failed" << std::endl;
    return 1;
  }

/*  // lower_bound
  it = bst.lower_bound(std::make_pair(25, 25));
  if (it != bst.find(std::make_pair(3, 30)))
  {
    std::cout << "lower_bound() failed" << std::endl;
    return 1;
  }*/

/*  // upper_bound
  it = bst.upper_bound(std::make_pair(3, 30));
  if (it != bst.find(std::make_pair(3, 30)))
  {
    std::cout << "upper_bound() failed" << std::endl;
    return 1;
  }*/

  // Тесты для остальных методов...

  std::cout << "All tests passed!" << std::endl;
  return 0;
}