#ifndef SPBSPU_LABS_2023_AADS_904_A_BINARYSEARCHTREE_H
#define SPBSPU_LABS_2023_AADS_904_A_BINARYSEARCHTREE_H
#include <cstddef>
#include <algorithm>
#include <iterator>
#include "twoThreeTreeIterator.h"
namespace dimkashelk
{
  namespace details
  {
    template< typename Key, typename Value, typename Compare >
    struct NodeOfTwoThreeTree
    {
    public:
      using node_type = NodeOfTwoThreeTree< Key, Value, Compare >;
      Key *key;
      Value *value;
      unsigned size;
      node_type *first;
      node_type *second;
      node_type *third;
      node_type *fourth;
      node_type *parent;
      NodeOfTwoThreeTree():
        key(static_cast< Key* >(::operator new[](sizeof(Key) * 3))),
        value(static_cast< Value* >(::operator new[](sizeof(Value) * 3))),
        size(0),
        first(nullptr),
        second(nullptr),
        third(nullptr),
        fourth(nullptr),
        parent(nullptr),
        compare_(Compare())
      {}
      NodeOfTwoThreeTree(const Key &k, const Value &v):
        key(static_cast< Key* >(::operator new[](sizeof(Key) * 3))),
        value(static_cast< Value* >(::operator new[](sizeof(Value) * 3))),
        size(1),
        first(nullptr),
        second(nullptr),
        third(nullptr),
        fourth(nullptr),
        parent(nullptr),
        compare_(Compare())
      {
        key[0] = key;
        value[0] = value;
      }
      NodeOfTwoThreeTree(const Key &k, const Value &v, node_type *fi, node_type *s, node_type *t, node_type *fo, node_type *p):
        key(static_cast< Key* >(::operator new[](sizeof(Key) * 3))),
        value(static_cast< Value* >(::operator new[](sizeof(Value) * 3))),
        size(1),
        first(fi),
        second(s),
        third(t),
        fourth(fo),
        parent(p),
        compare_(Compare())
      {
        key[0] = key;
        value[0] = value;
      }
      ~NodeOfTwoThreeTree()
      {
        ::operator delete[](key);
        ::operator delete[](value);
      }
      bool isList() const
      {
        return (first == nullptr) && (second == nullptr) && (third == nullptr);
      }
      void insert(const Key &k, const Value &v)
      {
        key[size] = k;
        value[size] = v;
        size++;
        sort();
      }
      void becomeNode2(const Key &k, const Value &v, node_type *first_, node_type *second_)
      {
        key[0] = k;
        value[0] = v;
        first = first_;
        second = second_;
        third = nullptr;
        fourth = nullptr;
        parent = nullptr;
        size = 1;
      }
      node_type *getLastChildren()
      {
        return (third)? third: (second)? second: first;
      }
      bool contains(const Key &k)
      {
        for (unsigned int i = 0; i < size; ++i)
        {
          if (key[i] == k)
          {
            return true;
          }
        }
        return false;
      }
    private:
      Compare compare_;
      void sort()
      {
        if (!compare_(key[0], key[1]))
        {
          std::swap(key[0], key[1]);
          std::swap(value[0], value[1]);
        }
        if (size == 3)
        {
          if (!compare_(key[0], key[2]))
          {
            std::swap(key[0], key[2]);
            std::swap(value[0], value[2]);
          }
          if (!compare_(key[1], key[2]))
          {
            std::swap(key[1], key[2]);
            std::swap(value[1], value[2]);
          }
        }
      }
    };
  }
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTree
  {
  using node_type = details::NodeOfTwoThreeTree< Key, Value, Compare >;
  using two_three_tree_type = TwoThreeTree< Key, Value, Compare >;
  public:
    using iterator = dimkashelk::TwoThreeTreeIterator<Key, Value, Compare>;
    TwoThreeTree():
      root_(nullptr),
      compare_(Compare())
    {}
    TwoThreeTree(const two_three_tree_type &tree):
      root_(nullptr),
      compare_(Compare())
    {
      copy(tree);
    }
    TwoThreeTree(two_three_tree_type &&tree):
      root_(tree.root_),
      compare_(Compare())
    {
      tree.root_ = nullptr;
    }
    two_three_tree_type &operator=(const two_three_tree_type &tree)
    {
      if (std::addressof(tree) == this)
      {
        return *this;
      }
      free();
      copy(tree);
      return *this;
    }
    two_three_tree_type &operator=(two_three_tree_type &&tree)
    {
      if (std::addressof(tree) == this)
      {
        return *this;
      }
      free();
      root_ = tree.root_;
      tree.root_ = nullptr;
      return *this;
    }
    ~TwoThreeTree()
    {
      free();
    }
    void insert(const Key &k, const Value &v)
    {
      root_ = insert(root_, k, v);
    }
    bool empty() const
    {
      return root_ == nullptr;
    }
    Value &get(const Key &k)
    {
      node_type *node = search(root_, k);
      if (node)
      {
        if (k == node->key[0])
        {
          return node->value[0];
        }
        else if (node->size == 2 && k == node->key[1])
        {
          return node->value[1];
        }
      }
      throw std::logic_error("No element");
    }
    bool contains(const Key &k) const
    {
      node_type *node = search(root_, k);
      return node && (k == node->key[0] || (node->size == 2 && k == node->key[1]));
    }
    void free()
    {
      free(root_);
      delete root_;
      root_ = nullptr;
    }
    iterator begin() const
    {
      return Iterator(iterator::goDown(root_));
    }
    iterator end() const
    {
      return iterator(nullptr);
    }
    friend bool operator>(const two_three_tree_type &first, const two_three_tree_type &second)
    {
      auto first_start = first.begin();
      auto second_start = second.begin();
      auto first_end = first.end();
      auto second_end = second.end();
      while (first_start != first_end && second_start != second_end)
      {
        if (*first_start != *second_start)
        {
          return *first_start > *second_start;
        }
        first_start++;
        second_start++;
      }
      if (first_start == first_end && second_start != second_end)
      {
        return true;
      }
      else if (first_start != first_end && second_start == second_end)
      {
        return false;
      }
      else
      {
        return false;
      }
    }
  private:
    node_type *root_;
    Compare compare_;
    node_type *insert(node_type *p, const Key &k, const Value &v) {
      if (!p)
      {
        return new node_type(k, v);
      }
      if (p->contains(k))
      {
        if (p->key[0] == k)
        {
          p->value[0] = v;
        }
        else if (p->key[1] == k)
        {
          p->value[1] = v;
        }
        return split(p);
      }
      if (p->isList())
      {
        p->insert(k, v);
      }
      else if (compare_(k, p->key[0]) && k != p->key[0])
      {
        insert(p->first, k, v);
      }
      else if (((p->size == 1) || ((p->size == 2) && compare_(k, p->key[1]))) && k != p->key[1])
      {
        insert(p->second, k, v);
      }
      else if (k != p->key[2])
      {
        insert(p->third, k, v);
      }
      return split(p);
    }
    node_type *split(node_type *item)
    {
      if (item->size < 3)
      {
        return item;
      }
      auto *x = new node_type(item->key[0], item->value[0], item->first, item->second, nullptr, nullptr, item->parent);
      auto *y = new node_type(item->key[2], item->value[2], item->third, item->fourth, nullptr, nullptr, item->parent);
      if (x->first)
      {
        x->first->parent = x;
      }
      if (x->second)
      {
        x->second->parent = x;
      }
      if (y->first)
      {
        y->first->parent = y;
      }
      if (y->second)
      {
        y->second->parent = y;
      }
      if (item->parent)
      {
        item->parent->insert(item->key[1], item->value[1]);
        if (item->parent->first == item)
        {
          item->parent->first = nullptr;
        }
        else if (item->parent->second == item)
        {
          item->parent->second = nullptr;
        }
        else if (item->parent->third == item)
        {
          item->parent->third = nullptr;
        }
        if (item->parent->first == nullptr)
        {
          item->parent->fourth = item->parent->third;
          item->parent->third = item->parent->second;
          item->parent->second = y;
          item->parent->first = x;
        }
        else if (item->parent->second == nullptr)
        {
          item->parent->fourth = item->parent->third;
          item->parent->third = y;
          item->parent->second = x;
        }
        else
        {
          item->parent->fourth = y;
          item->parent->third = x;
        }
        node_type *tmp = item->parent;
        delete item;
        return tmp;
      }
      else
      {
        x->parent = item;
        y->parent = item;
        item->becomeNode2(item->key[1], item->value[1], x, y);
        return item;
      }
    }
    node_type *search(node_type *node, const Key &k) const
    {
      if (!node)
      {
        return nullptr;
      }
      if (node->contains(k))
      {
        return node;
      }
      else if (compare_(k, node->key[0]))
      {
        return search(node->first, k);
      }
      else if ((node->size == 2 && compare_(k, node->key[1])) || node->size == 1)
      {
        return search(node->second, k);
      }
      else if (node->size == 2)
      {
        return search(node->third, k);
      }
      return nullptr;
    }
    void free(node_type *node)
    {
      if (node == nullptr)
      {
        return;
      }
      if (node->getLastChildren() == nullptr)
      {
        return;
      }
      free(node->first);
      delete node->first;
      node->first = nullptr;
      free(node->second);
      delete node->second;
      node->second = nullptr;
      if (node->size == 2)
      {
        free(node->third);
        delete node->third;
        node->third = nullptr;
      }
    }
    void copy(const two_three_tree_type &tree)
    {
      for (auto iter = tree.begin(); iter != tree.end(); iter++)
      {
        insert(*iter, iter.value);
      }
    }
  };
}
#endif
