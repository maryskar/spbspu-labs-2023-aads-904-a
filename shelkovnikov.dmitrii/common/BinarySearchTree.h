#ifndef COMMON_BINARYSEARCHTREE_H
#define COMMON_BINARYSEARCHTREE_H
namespace dimkashelk
{
  template< typename Key, typename Value, typename Compare >
  class BinarySearchTree
  {
  public:
    BinarySearchTree():
      root_(nullptr)
    {}
    void insert(const Key &key, const Value &value)
    {
      insert(root_, key, value);
    }
  private:
    struct Node {
      Key key;
      Value value;
      Node *left;
      Node *right;
      size_t height;
      Node(const Key &key, const Value &value):
        key(key),
        value(value)
        left(nullptr),
        right(nullptr),
        height(0)
      {}
    };
    Node *root_;
    int getHeight(Node *node) const
    {
      return node == nullptr? -1: node->height;
    }
    int getBalanceFactor(Node *node) const
    {
      return getHeight(node->left) - getHeight(node->right);
    }
    void rotateLeft(Node *&node)
    {
      Node *temp = node->right;
      node->right = temp->left;
      temp->left = node;
      node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
      temp->height = std::max(getHeight(temp->left), getHeight(temp->right)) + 1;
      node = temp;
    }
    void rotateRight(Node *&node) {
      Node *temp = node->left;
      node->left = temp->right;
      temp->right = node;
      node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
      temp->height = std::max(getHeight(temp->left), getHeight(temp->right)) + 1;
      node = temp;
    }
    void rebalance(Node *&node)
    {
      int balanceFactor = getBalanceFactor(node);
      if (balanceFactor > 1)
      {
        if (getBalanceFactor(node->left) < 0)
        {
          rotateLeft(node->left);
        }
        rotateRight(node);
      }
      else if (balanceFactor < -1)
      {
        if (getBalanceFactor(node->right) > 0)
        {
          rotateRight(node->right);
        }
        rotateLeft(node);
      }
    }
    void insert(Node *&node, const Key &key, const Value &value, bool &needToUpdateHeight)
    {
      if (node == nullptr)
      {
        node = new Node(key, value);
        return;
      }
      int res = compare(data, node->data);
      if (res == 0)
      {
        needToUpdateHeight = false;
        node->value = value;
        return;
      }
      else if (res < 0)
      {
        insert(node->left, data);
      }
      else
      {
        insert(node->right, data);
      }
      if (needToUpdateHeight)
      {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
      }
      rebalance(node);
    }
  };
}
#endif
