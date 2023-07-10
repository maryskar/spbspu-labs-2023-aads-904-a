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

  auto b = tree.insert(85);
  tree.insert(80);
  auto a = tree.insert(90);
  tree.insert(78);
  tree.insert(92);
  tree.insert(89);
  tree.insert(91);
  tree.insert(60);
  tree.insert(65);
  auto c = tree.insert(92);


//  tree.remove(92);
//  tree.leftRotation();
//  tree.rightRotation();
//  auto t = tree.searchNode(d6);

//  std::cout << tree.find(d8)->data_ << "\n";
//  tree.leftRotation(tree.find(d8));
//  tree.rightRotation(tree.find(d3));
//  auto f = tree.find(92);
  auto it_b = tree.begin();
  auto it_e = tree.end();
  auto it_bb = tree.beforeBegin();
  auto it = tree.begin();
  ++it_bb;
  --it_e;
  while (it != tree.end())
  {
    std::cout << *(it++) << " ";
  }
  std::cout << "\n";
  std::cout << *it_bb  << " ";
  std::cout << *it_b << " ";
  std::cout << *it_e << "\n";

//  std::cout << (f != tree.cend() ? *f : false) << "\n";

  std::cout << tree.SubTreeAsString();
  std::cout << "\n";

  tarasenko::RedBlackTree< int, std::less<> > rb;
}