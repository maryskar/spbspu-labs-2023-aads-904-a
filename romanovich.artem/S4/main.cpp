#include "binary_search_tree.h"
#include <iostream>
int main()
{
  using Key = int;
  using Value = int;

  using Compare = std::less< int >;
  // using data_type = std::pair< Key, Value >;
  using bst_t = BinarySearchTree< Key, Value, Compare >;
  // using tree_t = TreeNode< data_type >;
  using iterator = BidirectionalIterator< Key, Value, Compare >;
  using const_iterator = ConstBidirectionalIterator< Key, Value, Compare >;

  // Test BinarySearchTree constructor, insert, and size
  bst_t bst;
  bst.insert(5, 5);
  bst.insert(3, 3);
  bst.insert(7, 7);
  std::cout << "Size of BST: " << bst.size() << std::endl; // Expected output: 3

  // Test find
  iterator it_find_5 = bst.find(5);
  if (it_find_5 == bst.end() || it_find_5->second != 5)
  {
    std::cout << "Test find - FAIL" << std::endl;
    return 1;
  }

  // Test const_iterator and cend
  const_iterator cit = bst.cbegin();
  const_iterator cit_end = bst.cend();
  if (cit != cit_end)
  {
    std::cout
      << cit->first << ": "
      << cit->second << std::endl;
    ++cit;
  }

  // Test operator[]
  bst[10] = 10;
  std::cout << "Size of BST after operator[]: " << bst.size() << std::endl; // Expected output: 4

  // Test at
  std::cout << "Value at key 10: " << bst.at(10) << std::endl; // Expected output: 10

  // Test remove
  bst.remove(10);
  std::cout << "Size of BST after remove: " << bst.size() << std::endl; // Expected output: 3

  // Test clear and isEmpty
  bst.clear();
  std::cout << "Is BST empty? " << (bst.isEmpty() ? "Yes" : "No") << std::endl; // Expected output: Yes

  std::cout << "Tests OK" << std::endl;
  return 0;
}
