#include <iostream>
#include "BinarySearchTree.h"
#include "Tree.h"

using tree_t = tarasenko::details::Tree< std::pair< int, char >, std::less< >>;

template< typename Key, typename Value >
std::ostream& operator<<(std::ostream& out, const std::pair< Key, Value >& data)
{
  return out << "{" << data.first << " - " << data.second << "}";
}

template< typename T, typename Compare >
void printTree(tarasenko::details::Tree< T, Compare >* ptree)
{
  if (ptree == nullptr)
  {
    return;
  }
  printTree(ptree->left_);
  std::cout << ptree->data_ << " ";
  printTree(ptree->right_);
}

template< typename T, typename Compare >
tree_t* searchNode(tree_t* root, const T& data)
{
  auto comp = root->compare_;
  if (root == nullptr || root->data_ == data)
  {
    return root;
  }
  if (comp(data, root->data_))
  {
    return searchNode< T, Compare >(root->left_, data);
  }
  return searchNode< T, Compare >(root->right_, data);
}

template< typename T, typename Compare >
T getParent(tree_t* ptree)
{
  return ptree->parent_->data_;
}

int main()
{
  //using tree_t = tarasenko::BinarySearchTree<int, char, std::less<>>;

  tree_t* tree = nullptr;
  std::pair< int, char > d1{1, 'q'};
  std::pair< int, char > d2{2, 'w'};
  std::pair< int, char > d3{3, 'e'};
  std::pair< int, char > d4{7, 'q'};
  std::pair< int, char > d5{5, 'w'};
  std::pair< int, char > d6{9, 'e'};
  tree = insert(d1, tree);
  tree = insert(d2, tree);
  tree = insert(d3, tree);
  tree = insert(d5, tree);
  tree = insert(d4, tree);
  tree = insert(d6, tree);
  printTree(tree);
  auto t = searchNode< std::pair< int, char >, std::less< >>(tree, d3);
  std::cout << getParent< std::pair< int, char >, std::less< >>(t);
  deleteTree(tree);
}