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
    void insert(Node *&node, const T &data)
    {
      if (node == nullptr)
      {
        node = new Node(data);
        return;
      }
      if (data < node->data)
      {
        insert(node->left, data);
      }
      else if (data > node->data)
      {
        insert(node->right, data);
      }
      node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
      //rebalance(node);
    }
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
