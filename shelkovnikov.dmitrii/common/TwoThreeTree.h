#ifndef COMMON_BINARYSEARCHTREE_H
#define COMMON_BINARYSEARCHTREE_H
#include <cstddef>
#include <algorithm>
namespace details
{
  template< typename Key, typename Value >
  struct NodeOfTwoThreeTree
  {
    Key keys[2];
    Value value[2];
    NodeOfTwoThreeTree* children[3];
    NodeOfTwoThreeTree* parent;
    int keyCount;
    NodeOfTwoThreeTree():
      keys(),
      children(),
      parent(nullptr),
      keyCount(0)
    {}
  };
}
namespace dimkashelk
{
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTree
  {
  using node_type = details::NodeOfTwoThreeTree< Key, Value >;
  public:
    class Iterator
    {
    friend class TwoThreeTree< Key, Value, Compare >;
    public:
      Iterator &operator++()
      {
        next();
        return *this;
      }
      Iterator &operator++(int)
      {
        next();
        return *this;
      }
    private:
      node_type *node_;
      explicit Iterator(const node_type *node):
        node_(node)
      {};
      void *next()
      {
        if (node_->children[0] != nullptr)
        {
          node_ = node_->children[0];
          while (node_->children[2] != nullptr)
          {
            node_ = node_->children[2];
          }
        }
        else if (node_->children[1] != nullptr)
        {
          node_ = node_->children[1];
        }
        else if (node_->parent != nullptr)
        {
          node_type *parent = node_->parent;
          while (node_ == parent->children[1])
          {
            node_ = parent;
            parent = parent->parent;
          }
          if (node_ == parent->children[0])
          {
            node_ = parent;
          }
        }
        else
        {
          node_ = nullptr;
        }
      }
    };
    TwoThreeTree():
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
    void rotateRight(node_type *&node)
    {
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
