#ifndef SPBSPU_LABS_2023_AADS_904_A_BINARYSEARCHTREE_H
#define SPBSPU_LABS_2023_AADS_904_A_BINARYSEARCHTREE_H
#include <cstddef>
#include <algorithm>
#include <iterator>
#include "nodeToInsert.h"
#include "nodeOfTwoThreeTree.h"
#include "twoThreeTreeIterator.h"
#include "twoThreeTreeIteratorConst.h"
#include "twoThreeTreeReverseIterator.h"
#include "twoThreeTreeReverseIteratorConst.h"
#include "math_functions.h"
namespace dimkashelk
{
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTree
  {
  using node_to_insert = details::NodeToInsert< Key, Value, Compare >;
  using node_type = details::NodeOfTwoThreeTree< Key, Value, Compare >;
  using two_three_tree_type = TwoThreeTree< Key, Value, Compare >;
  using reference = std::pair< Key, Value >&;
  using const_reference = const std::pair< Key, Value >&;
  friend class TwoThreeTreeIterator< Key, Value, Compare >;
  friend class TwoThreeTreeIteratorConst< Key, Value, Compare >;
  public:
    using iterator = dimkashelk::TwoThreeTreeIterator< Key, Value, Compare >;
    using const_iterator = dimkashelk::TwoThreeTreeIteratorConst< Key, Value, Compare >;
    using reverse_iterator = dimkashelk::TwoThreeTreeReverseIterator< Key, Value, Compare >;
    using const_reverse_iterator = dimkashelk::TwoThreeTreeReverseIteratorConst< Key, Value, Compare >;
    using key_type = Key;
    using compare_type = Compare;
    TwoThreeTree():
      fakeNode_(static_cast< node_type* >(::operator new(sizeof(node_type)))),
      root_(nullptr),
      to_insert_(nullptr),
      compare_(Compare()),
      size_(0),
      was_updated_while_insert_(false)
    {}
    TwoThreeTree(const two_three_tree_type &tree):
      fakeNode_(static_cast< node_type* >(::operator new(sizeof(node_type)))),
      root_(nullptr),
      to_insert_(nullptr),
      compare_(Compare()),
      size_(0),
      was_updated_while_insert_(false)
    {
      copy(tree);
    }
    TwoThreeTree(two_three_tree_type &&tree):
      fakeNode_(static_cast< node_type* >(::operator new(sizeof(node_type)))),
      root_(tree.root_),
      to_insert_(tree.to_insert_),
      compare_(Compare()),
      size_(tree.size_),
      was_updated_while_insert_(false)
    {
      tree.root_ = nullptr;
      tree.to_insert_ = nullptr;
    }
    two_three_tree_type &operator=(const two_three_tree_type &tree)
    {
      if (std::addressof(tree) == this)
      {
        return *this;
      }
      clear();
      copy(tree);
      return *this;
    }
    two_three_tree_type &operator=(two_three_tree_type &&tree)
    {
      if (std::addressof(tree) == this)
      {
        return *this;
      }
      clear();
      root_ = tree.root_;
      tree.root_ = nullptr;
      to_insert_ = tree.to_insert_;
      tree.to_insert_ = nullptr;
      size_ = tree.size_;
      return *this;
    }
    ~TwoThreeTree()
    {
      clear();
      ::operator delete(fakeNode_);
    }
    Value &operator[](const Key &k)
    {
      try
      {
        return get(k);
      }
      catch (...)
      {
        insert(k, Value());
        return get(k);
      }
    }
    reference front()
    {
      return iterator(iterator::goDown(root_)).value_;
    }
    const_reference front() const
    {
      return iterator(iterator::goDown(root_)).value_;
    }
    iterator beforeBegin()
    {
      return iterator(fakeNode_, this);
    }
    const_iterator cbeforeBegin()
    {
      return const_iterator(fakeNode_, this);
    }
    iterator begin()
    {
      return iterator(iterator::goDown(root_), this);
    }
    const_iterator cbegin() const
    {
      return const_iterator(iterator::goDown(root_), this);
    }
    reverse_iterator rbegin() const
    {
      return reverse_iterator(iterator::goDownBack(root_), this);
    }
    const_reverse_iterator crbegin() const
    {
      return const_reverse_iterator(iterator::goDownBack(root_), this);
    }
    iterator end()
    {
      return iterator(nullptr, this);
    }
    const_iterator cend() const
    {
      return const_iterator(nullptr, this);
    }
    reverse_iterator rend()
    {
      return reverse_iterator(nullptr, this);
    }
    const_reverse_iterator crend()
    {
      return const_reverse_iterator(nullptr, this);
    }
    bool empty() const
    {
      return root_ == nullptr;
    }
    size_t size() const
    {
      return size_;
    }
    void clear() noexcept
    {
      free(root_);
      delete root_;
      root_ = nullptr;
      size_ = 0;
    }
    void insert(const Key &k, const Value &v)
    {
      root_ = insert(root_, k, v);
      if (was_updated_while_insert_)
      {
        was_updated_while_insert_ = false;
      }
      else
      {
        size_++;
      }
    }
    iterator eraseAfter(const_iterator pos)
    {
      root_ = remove(pos.node_, pos.value_.first);
      pos++;
      size_--;
      return iterator(pos.node_);
    }
    iterator eraseAfter(const_iterator first, const_iterator last)
    {
      for (; first != last; first++)
      {
        erase_after(first);
      }
      size_--;
      return iterator(last.node_);
    }
    Value &get(const Key &k)
    {
      node_type *node = search(root_, k);
      if (node)
      {
        if (details::isEqual< Key, Compare >(k, node->data[0].first))
        {
          return node->data[0].second;
        }
        else if (node->size == 2 && details::isEqual< Key, Compare >(k, node->data[1].first))
        {
          return node->data[1].second;
        }
      }
      throw std::logic_error("No element");
    }
    bool contains(const Key &k) const
    {
      node_type *node = search(root_, k);
      bool isEqualFirst = details::isEqual< Key, Compare >(k, node->data[0].first);
      bool isEqualSecond = (node->size == 2 && k == details::isEqual< Key, Compare >(k, node->data[1].first));
      return node && (isEqualFirst || isEqualSecond);
    }
  private:
    node_type *fakeNode_;
    node_type *root_;
    node_to_insert *to_insert_;
    Compare compare_;
    size_t size_;
    bool was_updated_while_insert_;
    node_type *getNewNodeFromLeftChild()
    {
      node_type *new_node = new node_type(to_insert_->data[0].first, to_insert_->data[0].second);
      new_node->first = to_insert_->first;
      new_node->second = to_insert_->second;
      new_node->parent = to_insert_->parent;
      return new_node;
    }
    node_type *getNewNodeFromRightChild()
    {
      node_type *new_node = new node_type(to_insert_->data[2].first, to_insert_->data[2].second);
      new_node->first = to_insert_->first;
      new_node->second = to_insert_->third;
      new_node->parent = to_insert_->fourth;
      return new_node;
    }
    node_type *insert(node_type *p, const Key &k, const Value &v) {
      if (!p)
      {
        return new node_type(k, v);
      }
      if (p->contains(k))
      {
        if (details::isEqual< Key, Compare >(p->data[0].first, k))
        {
          p->data[0].second = v;
        }
        else if (details::isEqual< Key, Compare >(p->data[1].first, k))
        {
          p->data[1].second = v;
        }
        was_updated_while_insert_ = true;
        return p;
      }
      if (p->isList())
      {
        if (p->size < 2)
        {
          p->insert(k, v);
          return p;
        }
        else
        {
          if (to_insert_)
          {
            delete to_insert_;
          }
          to_insert_ = new node_to_insert(p);
          to_insert_->insert(k, v);
        }
      }
      else if (compare_(k, p->data[0].first) && details::isNotEqual< Key, Compare >(p->data[0].first, k))
      {
        insert(p->first, k, v);
      }
      else if (((p->size == 1) || ((p->size == 2) && compare_(k, p->data[1].first))))
      {
        insert(p->second, k, v);
      }
      else if (details::isNotEqual< Key, Compare >(p->data[2].first, k))
      {
        insert(p->third, k, v);
      }
      return split(p);
    }
    node_type *split(node_type *item)
    {
      if (!to_insert_)
      {
        return item;
      }
      auto *x = getNewNodeFromLeftChild();
      auto *y = getNewNodeFromRightChild();
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
      if (to_insert_->parent)
      {
        auto *parent = to_insert_->parent;
        if (parent->size == 2)
        {
          node_to_insert *new_node = new node_to_insert(parent);
          new_node->insert(to_insert_->data[1].first, to_insert_->data[1].second);
          if (details::isEqual< Key, Compare >(new_node->data[0].first, to_insert_->data[1].first))
          {
            new_node->first = x;
            new_node->second = y;
            new_node->third = item->first;
            new_node->fourth = item->second;
          }
          else if (details::isEqual< Key, Compare >(new_node->data[1].first, to_insert_->data[1].first))
          {
            new_node->first = item->first;
            new_node->second = x;
            new_node->third = y;
            new_node->fourth = item->second;
          }
          else if (details::isEqual< Key, Compare >(new_node->data[2].first, to_insert_->data[1].first))
          {
            new_node->first = item->first;
            new_node->second = item->second;
            new_node->third = x;
            new_node->fourth = y;
          }
          delete to_insert_;
          to_insert_ = new_node;
        }
        else
        {
          parent->insert(to_insert_->data[1].first, to_insert_->data[1].second);
          if (parent->first == item)
          {
            parent->third = item->parent->second;
            parent->second = y;
            parent->first = x;
          }
          else if (parent->second == item)
          {
            item->parent->third = y;
            item->parent->second = x;
            delete item;
          }
          delete to_insert_;
          to_insert_ = nullptr;
        }
      }
      else
      {
        node_type *parent = new node_type(to_insert_->data[1].first, to_insert_->data[1].second);
        parent->first = x;
        parent->second = y;
        x->parent = parent;
        y->parent = parent;
        delete item;
        delete to_insert_;
        to_insert_ = nullptr;
        return parent;
      }
      return item;
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
      else if (compare_(k, node->data[0].first))
      {
        return search(node->first, k);
      }
      else if ((node->size == 2 && compare_(k, node->data[1].first)) || node->size == 1)
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
      for (auto iter = tree.cbegin(); iter != tree.cend(); iter++)
      {
        insert(iter->first, iter->second);
      }
    }
    node_type *remove(node_type *p, Key k)
    {
      node_type *item = search(p, k);
      if (!item)
      {
        return p;
      }
      node_type *min = nullptr;
      if (details::isEqual< Key, Compare >(item->data[0].first, k))
      {
        min = iterator::goDown(item->second);
      }
      else
      {
        min = iterator::goDown(item->third);
      }
      if (min)
      {
        std::pair< Key, Value > &z = (k == item->data[0].first? item->data[0]: item->data[1]);
        std::swap(z, min->data[0]);
        item = min;
      }
      item->removeFromNode(k);
      return fix(item);
    }
    node_type *fix(node_type *leaf)
    {
      if (leaf->size == 0 && leaf->parent == nullptr)
      {
        delete leaf;
        return nullptr;
      }
      if (leaf->size != 0)
      {
        if (leaf->parent)
        {
          return fix(leaf->parent);
        }
        else
        {
          return leaf;
        }
      }
      node_type *parent = leaf->parent;
      if (parent->first->size == 2 || parent->second->size == 2 || parent->size == 2)
      {
        leaf = rebalance(leaf);
      }
      else if (parent->size == 2 && parent->third->size == 2)
      {
        leaf = rebalance(leaf);
      }
      else
      {
        leaf = merge(leaf);
      }
      return fix(leaf);
    }
    node_type *rebalance(node_type *node)
    {
      node_type *parent = node->parent;
      node_type *first = parent->first;
      node_type *second = parent->second;
      node_type *third = parent->third;
      if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2))
      {
        if (first == node)
        {
          parent->first = parent->second;
          parent->second = parent->third;
          parent->third = nullptr;
          parent->first->insert(parent->data[0].first, parent->data[0].second);
          parent->first->third = parent->first->second;
          parent->first->second = parent->first->first;
          if (node->first != nullptr)
          {
            parent->first->first = node->first;
          }
          else if (node->second != nullptr)
          {
            parent->first->first = node->second;
          }
          if (parent->first->first != nullptr)
          {
            parent->first->first->parent = parent->first;
          }
          parent->removeFromNode(parent->data[0].first);
          delete first;
        }
        else if (second == node)
        {
          first->insert(parent->data[0].first, parent->data[0].second);
          parent->removeFromNode(parent->data[0].first);
          if (node->first != nullptr)
          {
            first->third = node->first;
          }
          else if (node->second != nullptr)
          {
            first->third = node->second;
          }
          if (first->third != nullptr)
          {
            first->third->parent = first;
          }
          parent->second = parent->third;
          parent->third = nullptr;
          delete second;
        }
        else if (third == node)
        {
          second->insert(parent->data[1].first, parent->data[1].second);
          parent->third = nullptr;
          parent->removeFromNode(parent->data[1].first);
          if (node->first != nullptr)
          {
            second->third = node->first;
          }
          else if (node->second != nullptr)
          {
            second->third = node->second;
          }
          if (second->third != nullptr)
          {
            second->third->parent = second;
          }
          delete third;
        }
      }
      else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2)))
      {
        if (third == node)
        {
          if (node->first != nullptr)
          {
            node->second = node->first;
            node->first = nullptr;
          }
          node->insert(parent->data[1].first, parent->data[1].second);
          if (second->size == 2)
          {
            parent->data[1] = second->data[1];
            second->removeFromNode(second->data[1].first);
            node->first = second->third;
            second->third = nullptr;
            if (node->first != nullptr)
            {
              node->first->parent = node;
            }
          }
          else if (first->size == 2)
          {
            parent->data[1] = second->data[0];
            node->first = second->second;
            second->second = second->first;
            if (node->first != nullptr)
            {
              node->first->parent = node;
            }
            second->data[0] = parent->data[0];
            parent->data[0] = first->data[1];
            first->removeFromNode(first->data[1].first);
            second->first = first->third;
            if (second->first != nullptr)
            {
              second->first->parent = second;
            }
            first->third = nullptr;
          }
        }
        else if (second == node)
        {
          if (third->size == 2)
          {
            if (node->first == nullptr)
            {
              node->first = node->second;
              node->second = nullptr;
            }
            second->insert(parent->data[1].first, parent->data[1].second);
            parent->data[1] = third->data[0];
            third->removeFromNode(third->data[0].first);
            second->second = third->first;
            if (second->second != nullptr)
            {
              second->second->parent = second;
            }
            third->first = third->second;
            third->second = third->third;
            third->third = nullptr;
          }
          else if (first->size == 2)
          {
            if (node->second == nullptr)
            {
              node->second = node->first;
              node->first = nullptr;
            }
            second->insert(parent->data[0].first, parent->data[0].second);
            parent->data[0] = first->data[1];
            first->removeFromNode(first->key[1]);
            second->first = first->third;
            if (second->first != nullptr)
            {
              second->first->parent = second;
            }
            first->third = nullptr;
          }
        }
        else if (first == node)
        {
          if (node->first == nullptr)
          {
            node->first = node->second;
            node->second = nullptr;
          }
          first->insert(parent->data[0].first, parent->data[0].second);
          if (second->size == 2)
          {
            parent->data[0] = second->data[0];
            second->removeFromNode(second->data[0].first);
            first->second = second->first;
            if (first->second != nullptr)
            {
              first->second->parent = first;
            }
            second->first = second->second;
            second->second = second->third;
            second->third = nullptr;
          }
          else if (third->size == 2)
          {
            parent->data[0] = second->data[0];
            second->data[0] = parent->data[1];
            parent->data[1] = third->data[0];
            third->removeFromNode(third->data[0].first);
            first->second = second->first;
            if (first->second != nullptr)
            {
              first->second->parent = first;
            }
            second->first = second->second;
            second->second = third->first;
            if (second->second != nullptr)
            {
              second->second->parent = second;
            }
            third->first = third->second;
            third->second = third->third;
            third->third = nullptr;
          }
        }
      }
      else if (parent->size == 1)
      {
        node->insert(parent->data[0].first, parent->data[0].second);
        if (first == node && second->size == 2)
        {
          parent->data[0] = second->data[0];
          second->removeFromNode(second->data[0].first);
          if (node->first == nullptr)
          {
            node->first = node->second;
          }
          node->second = second->first;
          second->first = second->second;
          second->second = second->third;
          second->third = nullptr;
          if (node->second != nullptr)
          {
            node->second->parent = node;
          }
        }
        else if (second == node && first->size == 2)
        {
          parent->data[0] = first->data[1];
          first->removeFromNode(first->data[1].first);
          if (node->second == nullptr)
          {
            node->second = node->first;
          }
          node->first = first->third;
          first->third = nullptr;
          if (node->first != nullptr)
          {
            node->first->parent = node;
          }
        }
      }
      return parent;
    }
    node_type *merge(node_type *leaf)
    {
      node_type *parent = leaf->parent;
      if (parent->first == leaf)
      {
        parent->second->insert(parent->data[0].first, parent->data[0].second);
        parent->second->third = parent->second->second;
        parent->second->second = parent->second->first;
        if (leaf->first != nullptr)
        {
          parent->second->first = leaf->first;
        }
        else if (leaf->second != nullptr)
        {
          parent->second->first = leaf->second;
        }
        if (parent->second->first != nullptr)
        {
          parent->second->first->parent = parent->second;
        }
        parent->removeFromNode(parent->data[0].first);
        delete parent->first;
        parent->first = nullptr;
      }
      else if (parent->second == leaf)
      {
        parent->first->insert(parent->data[0].first, parent->data[0].second);
        if (leaf->first != nullptr)
        {
          parent->first->third = leaf->first;
        }
        else if (leaf->second != nullptr)
        {
          parent->first->third = leaf->second;
        }
        if (parent->first->third != nullptr)
        {
          parent->first->third->parent = parent->first;
        }
        parent->removeFromNode(parent->data[0].first, parent->data[0].second);
        delete parent->second;
        parent->second = nullptr;
      }
      if (parent->parent == nullptr)
      {
        node_type *tmp = nullptr;
        if (parent->first != nullptr)
        {
          tmp = parent->first;
        }
        else
        {
          tmp = parent->second;
        }
        tmp->parent = nullptr;
        delete parent;
        return tmp;
      }
      return parent;
    }
  };
}
#endif
