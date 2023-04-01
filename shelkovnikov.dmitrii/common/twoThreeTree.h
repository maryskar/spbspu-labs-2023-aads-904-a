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
      value{Value(), Value(), Value()},
      size(0),
      first(nullptr),
      second(nullptr),
      third(nullptr),
      fourth(nullptr),
      parent(nullptr),
      compare_(Compare{})
    {}
    NodeOfTwoThreeTree(const Key &k, const Value &v):
      key{k, Key(), Key()},
      value{v, Value(), Value()},
      size(1),
      first(nullptr),
      second(nullptr),
      third(nullptr),
      fourth(nullptr),
      parent(nullptr),
      compare_(Compare{})
    {}
    NodeOfTwoThreeTree(const Key &k, const Value &v, node_type *fi, node_type *s, node_type *t, node_type *fo, node_type *p):
      key{k, Key(), Key()},
      value{v, Value(), Value()},
      size(1),
      first(fi),
      second(s),
      third(t),
      fourth(fo),
      parent(p),
      compare_(Compare{})
    {}
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
  private:
    Compare compare_;
    void sort()
    {
      if (!compare_(key[0], key[1]))
      {
        std::swap(key[0], key[1]);
        std::swap(value[0], value[1]);
      };
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
      Key first;
      Value second;
      explicit Iterator(node_type *node):
        first(node->key[0]),
        second(node->value[0]),
        node_(node),
        prev_(nullptr)
      {};
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
      node_type *prev_;
      void next()
      {
        if (node_->getLastChildren() == nullptr)
        {
          if (node_->size == 1)
          {
            node_type *new_node = goUp(node_);
            if (new_node->parent == nullptr)
            {
              throw std::runtime_error("End of tree");
            }
            node_ = new_node->parent;
            prev_ = new_node;
            if (prev_ == node_->first)
            {
              set(0);
            }
            else if (prev_ == node_->second && node_->size == 2)
            {
              set(1);
            }
          }
          else
          {
            if (first == node_->key[1])
            {
              prev_ = goUp(node_);
              node_ = prev_->parent;
              if (node_ == nullptr)
              {
                throw std::runtime_error("No parent");
              }
              if (node_->first == prev_)
              {
                set(0);
              }
              else
              {
                set(1);
              }
            }
            else
            {
              set(1);
            }
          }
        }
        else
        {
          if (node_->first == prev_)
          {
            node_ = goDown(node_->second);
          }
          else if (node_->second == prev_ && node_->size == 2)
          {
            node_ = goDown(node_->third);
          }
          prev_ = node_->parent;
          set(0);
        }
      }
      node_type *goUp(node_type *node)
      {
        node_type *parent = node->parent;
        while (parent && parent->getLastChildren() == node)
        {
          node = parent;
          parent = parent->parent;
        }
        return node;
      }
      static node_type *goDown(node_type *node)
      {
        while (node->first)
        {
          node = node->first;
        }
        return node;
      }
      void set(unsigned ind)
      {
        first = node_->key[ind];
        second = node_->value[ind];
      }
    };
    TwoThreeTree():
      root_(nullptr),
      compare_(Compare())
    {}
    ~TwoThreeTree()
    {
      free(root_);
      delete root_;
    }
    void insert(const Key &k, const Value &v) {
      root_ = insert(root_, k, v);
    }
    Iterator begin()
    {
      return Iterator(Iterator::goDown(root_));
    }
  private:
    node_type *root_;
    Compare compare_;
    node_type *insert(node_type *p, const Key &k, const Value &v) {
      if (!p)
      {
        return new node_type(k, v);
      }
      if (p->isList())
      {
        p->insert(k, v);
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
    void free(node_type *node)
    {
      if (node->getLastChildren() == nullptr)
      {
        return;
      }
      free(node->first);
      delete node->first;
      free(node->second);
      delete node->second;
      if (node->size == 2)
      {
        free(node->third);
        delete node->third;
      }
      delete node;
      return;
    }
  };
}
#endif
