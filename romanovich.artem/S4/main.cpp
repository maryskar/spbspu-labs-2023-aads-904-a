#include "binary_search_tree.h"
#include <iostream>
#include <cassert>
int main()
{
  using Key = int;
  using Value = int;
  using Compare = std::less< int >;
  using data_type = std::pair< Key, Value >;
  using bst_t = BinarySearchTree< Key, Value, Compare >;
  // using tree_t = TreeNode< data_type >;
  using iterator = BidirectionalIterator< Key, Value, Compare >;
  using const_iterator = ConstBidirectionalIterator< Key, Value, Compare >;

  // Test BinarySearchTree constructor, insert, and size
  bst_t bst;
  bst.insert(1, 1);
  bst.insert(3, 3);
  bst.insert(5, 5);
  iterator it = bst.begin();

  std::cout << it->second << std::endl;
  std::cout << "Size of BST: " << bst.size() << std::endl; // Expected output: 3

  bst.remove(10);
  std::cout << "Size of BST after remove: " << bst.size() << std::endl; // Expected output: 3

  // Test erase with iterator
  iterator it_erase = bst.find(5);
  bst.erase(it_erase);
  std::cout << "Size of BST after erase by iterator: " << bst.size() << std::endl; // Expected output: 2

  // Test erase with key
  size_t count_erased = bst.erase(3);
  std::cout << "Size of BST after erase by key: " << bst.size() << std::endl; // Expected output: 1
  std::cout << "Elements erased by key: " << count_erased << std::endl; // Expected output: 1

  // Test erase with range of iterators
  bst.insert(15, 15);
  bst.insert(12, 12);
  bst.insert(17, 17);
  std::cout << "Size of BST before erasing range: " << bst.size() << std::endl; // Expected output: 4
  iterator it_range_begin = bst.find(12);
  iterator it_range_end = bst.find(17);
  IteratorDto< data_type > it_range_b
  {
    it_range_begin.getRoot(),
    it_range_begin.getNode(),
    it_range_begin.getFakeNode()
  };
  IteratorDto< data_type > it_range_e
  {
    it_range_end.getRoot(),
    it_range_end.getNode(),
    it_range_end.getFakeNode()
  };
  bst.erase(const_iterator(it_range_b), const_iterator(it_range_e));
  std::cout << "Size of BST after erasing range: " << bst.size() << std::endl; // Expected output: 2

  // Test erase for a key that doesn't exist
  size_t count_erased_nonexistent = bst.erase(100);
  std::cout << "Size of BST after erase of nonexistent key: " << bst.size() << std::endl; // Expected output: 2
  std::cout << "Elements erased by nonexistent key: " << count_erased_nonexistent << std::endl; // Expected output: 0

  // Test clear and empty
  bst.clear();
  std::cout << "Is BST empty? " << (bst.empty() ? "Yes" : "No") << std::endl; // Expected output: Yes

  std::cout << "Tests OK" << std::endl;
  return 0;
}