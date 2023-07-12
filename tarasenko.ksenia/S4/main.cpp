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
//  auto it_b = tree.begin();
//  auto it_e = tree.end();
//  auto it_bb = tree.beforeBegin();
//  auto it = tree.begin();
//  ++it_bb;
//  --it_e;
//  std::cout << *it_bb  << " ";
//  std::cout << *it_b << " ";
//  std::cout << *it_e << "\n";

//======================================================================================

  tarasenko::RedBlackTree< int, std::less<> > rb;
  rb.insert(80);
  rb.insert(85);
  rb.insert(67);
  rb.insert(50);
  rb.insert(40);
  rb.insert(60);
  rb.insert(35);
  rb.insert(67);
  rb.insert(55);
  rb.insert(53);


//  rb.insert(1);
//  rb.insert(2);
//  rb.insert(3);
//  rb.insert(4);
//  rb.insert(5);
//  rb.insert(6);
//  rb.insert(7);
//  rb.insert(8);
//  rb.insert(9);
//  rb.insert(10);

//  tree.remove(92);

  auto it = rb.begin();
  while (it != rb.end())
  {
    std::cout << *(it++) << " ";
  }
  std::cout << "\n";

  std::cout << rb.printAsString() << "\n";
  std::cout << rb.printColorAsString();
}