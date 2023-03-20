#ifndef COMMON_BINARYSEARCHTREE_H
#define COMMON_BINARYSEARCHTREE_H
#include <cstddef>
#include <algorithm>
namespace details
{
  template< typename Key, typename Value >
  struct Node {
    Key key;
    Value value;
    Node *left;
    Node *right;
    Node *prev;
    size_t height;
    Node(const Key &key, const Value &value):
      key(key),
      value(value),
      left(nullptr),
      right(nullptr),
      prev(nullptr),
      height(0)
    {}
  };
}
namespace dimkashelk
{
  template< typename Key, typename Value, typename Compare >
  class BinarySearchTree
  {
  using node_type = details::Node< Key, Value >;
  public:
    class Iterator
    {
    friend class BinarySearchTree< Key, Value, Compare >;
    public:
      Iterator &operator++()
      {
        if (!visited_left)
        {
          node_ = node_->left;
        }
        else if (!visited_right)
        {
          node_ = node_->right;
        }
        else
        {
          node_ = node_->prev;
        }
      }
    private:
      node_type *node_;
      bool visited_left;
      bool visited_right;
      explicit Iterator(const node_type *node):
        node_(node),
        visited_left(false),
        visited_right(false)
      {};
      node_type *upToNext(node_type *node)
      {
        node_type *parent = node->prev;
        while (parent)
        {
          parent = node->prev;
          if (parent->left == node)
          {
            return parent;
          }
          node = node->prev;
        }
      }
    };
    BinarySearchTree():
      root_(nullptr)
    {}
    void insert(const Key &key, const Value &value)
    {
      bool needToUpdateHeight = true;
      insert(root_, key, value, needToUpdateHeight, nullptr);
    }
  private:
    node_type *root_;
    int getHeight(node_type *node) const
    {
      return node == nullptr? -1: node->height;
    }
    int getBalanceFactor(node_type *node) const
    {
      return getHeight(node->left) - getHeight(node->right);
    }
    void rotateLeft(node_type *&node)
    {
      node_type *temp = node->right;
      node->right = temp->left;
      temp->left = node;
      node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
      temp->height = std::max(getHeight(temp->left), getHeight(temp->right)) + 1;
      node = temp;
    }
    void rotateRight(node_type *&node) {
      node_type *temp = node->left;
      node->left = temp->right;
      temp->right = node;
      node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
      temp->height = std::max(getHeight(temp->left), getHeight(temp->right)) + 1;
      node = temp;
    }
    void rebalance(node_type *&node)
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
    void insert(node_type *&node, const Key &key, const Value &value, bool &needToUpdateHeight, node_type *prev)
    {
      if (node == nullptr)
      {
        node = new node_type(key, value);
        node->prev = prev;
        return;
      }
      int res = compare(key, node->key);
      if (res == 0)
      {
        needToUpdateHeight = false;
        node->value = value;
        return;
      }
      else if (res < 0)
      {
        insert(node->left, key, value, needToUpdateHeight, node);
      }
      else
      {
        insert(node->right, key, value, needToUpdateHeight, node);
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
