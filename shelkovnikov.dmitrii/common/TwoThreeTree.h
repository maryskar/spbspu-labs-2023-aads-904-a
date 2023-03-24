#ifndef COMMON_BINARYSEARCHTREE_H
#define COMMON_BINARYSEARCHTREE_H
#include <cstddef>
#include <algorithm>
#include <iterator>
namespace details
{
  template< typename Key, typename Value, typename Compare >
  struct NodeOfTwoThreeTree
  {
  public:
    using node_type = NodeOfTwoThreeTree< Key, Value, Compare >;
    Key key[3];
    Value value[3];
    unsigned size;
    node_type *first;
    node_type *second;
    node_type *third;
    node_type *fourth;
    node_type *parent;
    NodeOfTwoThreeTree():
      key{Key(), Key(), Key()},
      Value{Value(), Value(), Value()},
      size(0),
      first(nullptr),
      second(nullptr),
      third(nullptr),
      fourth(nullptr),
      parent(nullptr)
    {}
    NodeOfTwoThreeTree(Key &k, Value &v, node_type *fi, node_type *s, node_type *t, node_type *fo, node_type *p):
      key{k, Key(), Key()},
      value{v, Value(), Value()},
      size(1),
      first(fi),
      second(s),
      third(t),
      fourth(fo),
      parent(p)
    {}
    bool is_leaf() const
    {
      return (first == nullptr) && (second == nullptr) && (third == nullptr);
    }
    bool find(Key &k)
    {
      for (unsigned i = 0; i < size; ++i)
      {
        if (key[i] == k)
        {
          return true;
        }
      }
      return false;
    }
    void insert(Key &k, Value &v)
    {
      key[size] = k;
      value[size] = v;
      size++;
      sort();
    }
  private:
    void sort2()
    {
      if (!Compare(key[0], key[1]))
      {
        std::swap(key[0], key[1]);
        std::swap(value[0], value[1]);
      };
    }
    void sort3()
    {
      if (!Compare(key[0], key[1]))
      {
        std::swap(key[0], key[1]);
        std::swap(value[0], value[1]);
      }
      if (!Compare(key[0], key[2]))
      {
        std::swap(key[0], key[2]);
        std::swap(value[0], value[2]);
      }
      if (!Compare(key[1], key[2]))
      {
        std::swap(key[1], key[2]);
        std::swap(value[1], value[2]);
      }
    }
    void sort()
    {
      if (size == 2)
      {
        sort2();
      }
      else if (size == 3)
      {
        sort3();
      }
    }
  };
}
namespace dimkashelk
{
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTree
  {
  using node_type = details::NodeOfTwoThreeTree< Key, Value, Compare >;
  public:
    class Iterator
    {
      friend class TwoThreeTree< Key, Value, Compare >;
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
      explicit Iterator(const node_type *node):
        node_(node),
        first(node_->keys[0]),
        second(node_->value[0])
      {};
      void next()
      {}
    };
    TwoThreeTree():
      root_(nullptr),
      compare_(Compare())
    {}
    void insert(Key &k, Value &v) {
      root_ = insert(root_, k, v);
    }
  private:
    node_type *root_;
    Compare compare_;
    node_type *insert(node_type *p, Key &k, Value &v)
    {
      if (!p)
      {
        return new node_type(k);
      }
      if (p->is_leaf())
      {
        p->insert_to_node(k);
      }
      else if (compare_(k, p->key[0]))
      {
        insert(p->first, k, v);
      }
      else if ((p->size == 1) || ((p->size == 2) && compare_(k, p->key[1])))
      {
        insert(p->second, k, v);
      }
      else
      {
        insert(p->third, k, v);
      }
      return split(p);
    }
    node_type *split(node_type *item) {
      if (item->size < 3)
      {
        return item;
      }
      auto *x = new node_type(item->key[0], item->first, item->second, nullptr, nullptr, item->parent);
      auto *y = new node_type(item->key[2], item->third, item->fourth, nullptr, nullptr, item->parent);
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
        item->parent->insert_to_node(item->key[1]);
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
        item->become_node2(item->key[1], x, y);
        return item;
      }
    }
  };
}
#endif
