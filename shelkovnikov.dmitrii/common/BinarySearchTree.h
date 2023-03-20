#ifndef COMMON_BINARYSEARCHTREE_H
#define COMMON_BINARYSEARCHTREE_H
namespace dimkashelk
{
  template< typename Key, typename Value, typename Compare >
  class BinarySearchTree
  {
  public:
    BinarySearchTree():
      root(nullptr)
    {}
  private:
    struct Node {
      T data;
      Node *left;
      Node *right;
      int height;
      Node(const T &data):
        data(data),
        left(nullptr),
        right(nullptr),
        height(0)
      {}
    };
    Node *root;
  };
}
#endif
