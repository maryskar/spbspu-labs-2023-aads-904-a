#include "binary_search_tree.h"
#include <iostream>
int main()
{
  BinarySearchTree< int, int > bst;

  auto [it1, inserted1] = bst.insert(5, 5);
  auto [it2, inserted2] = bst.insert(3, 3);
  auto [it3, inserted3] = bst.insert(7, 7);
  if (!inserted1 || !inserted2 || !inserted3 || it1->second != 5 || it2->second != 3 || it3->second != 7)
  {
    std::cout << "Test insert - FAIL" << std::endl;
    return 1;
  }

  // Test finding elements
  auto it_find_5 = bst.find(5);
  auto it_find_3 = bst.find(3);
  auto it_find_7 = bst.find(7);
  auto it_find_1 = bst.find(1);
  if (it_find_5 == bst.end() || it_find_5->second != 5 ||
      it_find_3 == bst.end() || it_find_3->second != 3 ||
      it_find_7 == bst.end() || it_find_7->second != 7 ||
      it_find_1 != bst.end())
  {
    std::cout << "Test find - FAIL" << std::endl;
    return 1;
  }

  // Test removal
  bst.remove(5);
  auto it_after_remove = bst.find(5);
  if (it_after_remove != bst.end())
  {
    std::cout << "Test remove - FAIL" << std::endl;
    return 1;
  }
  std::cout << "Tests OK" << std::endl;
  return 0;
}
