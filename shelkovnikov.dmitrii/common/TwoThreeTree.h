#ifndef COMMON_BINARYSEARCHTREE_H
#define COMMON_BINARYSEARCHTREE_H
#include <cstddef>
#include <algorithm>
#include <iterator>
namespace details
{
  template< typename Key, typename Value >
  struct NodeOfTwoThreeTree
  {
    Key keys[2];
    Value values[2];
    NodeOfTwoThreeTree* children[3];
    NodeOfTwoThreeTree* parent;
    int keyCount;
    NodeOfTwoThreeTree():
      keys(),
      values(),
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
    using node_type = details::NodeOfTwoThreeTree<Key, Value>;
  public:
    class Iterator
    {
      friend class TwoThreeTree<Key, Value, Compare>;
    public:
      const Key first;
      Value second;
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
      unsigned index_;
      explicit Iterator(const node_type *node) :
        node_(node),
        index_(0),
        first(node_->keys[index_]),
        second(node_->value[index_])
      {
      };
      void next()
      {
      }
    };
    TwoThreeTree() :
      root_(nullptr)
    {
    }
    void insert(const Key &key, const Value &value)
    {
      if (!root_)
      {
        root_ = new node_type();
        root_->keys[0] = key;
        root_->values[0] = value;
        root_->keyCount = 1;
      }
      else
      {
        node_type *node = root_;
        node_type *parent = nullptr;
        int index = -1;
        while (node)
        {
          if (node->keyCount == 2)
          {
            split(node, parent, index);
            if (key > parent->keys[index])
            {
              node = parent->children[index + 1];
            }
            else
            {
              node = parent->children[index];
            }
          }
          parent = node;
          index = find_index(node, key);
          if (index < node->num_keys && node->keys[index] == key)
          {
            node->values[index] = value;
            return;
          }
          node = node->children[index];
        }
        parent->keys[parent->num_keys] = key;
        parent->values[parent->num_keys] = value;
        parent->keyCount++;
      }
    }
  private:
    node_type *root_;
    void split(node_type *node, node_type *parent, int index)
    {
      auto *new_node = new node_type();
      if (index == -1)
      {
        index = 0;
      }
      Key middle_key = node->keys[1];
      if (!node->is_leaf)
      {
        new_node->is_leaf = false;
        new_node->children[0] = node->children[2];
        node->children[2] = nullptr;
        new_node->children[1] = node->children[3];
        node->children[3] = nullptr;
      }
      new_node->keys[0] = node->keys[2];
      new_node->values[0] = node->values[2];
      node->keys[2] = Key();
      node->values[2] = Value();
      new_node->num_keys = 1;
      node->num_keys = 1;
      if (parent)
      {
        for (int i = parent->num_keys; i > index; i--)
        {
          parent->keys[i] = parent->keys[i - 1];
          parent->values[i] = parent->values[i - 1];
          parent->children[i + 1] = parent->children[i];
        }
        parent->keys[index] = middle_key;
        parent->values[index] = node->values[1];
        parent->children[index + 1] = new_node;
        parent->num_keys++;
      }
      else
      {
        parent = new node_type();
        parent->keys[0] = middle_key;
        parent->values[0] = node->values[1];
        parent->children[0] = node;
        parent->children[1] = new_node;
        parent->num_keys = 1;
        root_ = parent;
      }
    }
  };
}
#endif
