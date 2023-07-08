#include <iostream>
#include "BinarySearchTree.h"
#include "RedBlackTree.h"

template< typename Key, typename Value >
std::ostream& operator<<(std::ostream& out, const std::pair< Key, Value >& data)
{
  return out << "{" << data.first << " - " << data.second << "}";
}

int main()
{
  using tree_t = tarasenko::BinarySearchTree< int, std::less<> >;

  tree_t tree = tree_t();
  int d1{85};
  int d2{80};
  int d3{90};
  int d4{78};
  int d5{92};
  int d6{89};
  int d7{91};
  int d8{60};
  int d9{65};
  tree.insert(d1);
  tree.insert(d2);
  tree.insert(d3);
  tree.insert(d4);
  tree.insert(d5);
  tree.insert(d6);
  tree.insert(d7);
  tree.insert(d8);
  tree.insert(d9);

//  tree.remove(d1);
//  tree.leftRotation();
//  tree.rightRotation();
//  auto t = tree.searchNode(d6);

//  std::cout << tree.find(d8)->data_ << "\n";
//  tree.leftRotation(tree.find(d8));
//  tree.rightRotation(tree.find(d3));

  std::cout << tree.SubTreeAsString();
  std::cout << "\n";

//  auto t = tree.searchNode(d3);
//  std::cout << tarasenko::details::getParent(t);
//  deleteTree(tree);
  tarasenko::RedBlackTree< int, std::less<> > rb;
}