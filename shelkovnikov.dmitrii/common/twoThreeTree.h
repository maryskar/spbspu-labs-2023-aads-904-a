#ifndef SPBSPU_LABS_2023_AADS_904_A_BINARYSEARCHTREE_H
#define SPBSPU_LABS_2023_AADS_904_A_BINARYSEARCHTREE_H
#include <cstddef>
#include <algorithm>
#include <iterator>
#include "nodeOfTwoThreeTree.h"
#include "twoThreeTreeIterator.h"
#include "twoThreeTreeIteratorConst.h"
namespace dimkashelk
{
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTree
  {
  using node_type = details::NodeOfTwoThreeTree< Key, Value, Compare >;
  using two_three_tree_type = TwoThreeTree< Key, Value, Compare >;
  using value_type = std::pair< Key, Value >;
  using reference = std::pair< Key, Value >&;
  using const_reference = const std::pair< Key, Value >&;
  public:
    using iterator = dimkashelk::TwoThreeTreeIterator< Key, Value, Compare >;
    using const_iterator = dimkashelk::TwoThreeTreeIteratorConst< Key, Value, Compare >;
    TwoThreeTree():
      fakeNode_(static_cast< node_type* >(::operator new(sizeof(node_type)))),
      root_(nullptr),
      compare_(Compare())
    {
      fakeNode_->first = nullptr;
    }
    TwoThreeTree(const two_three_tree_type &tree):
      fakeNode_(static_cast< node_type* >(::operator new(sizeof(node_type)))),
      root_(nullptr),
      compare_(Compare())
    {
      fakeNode_->first = nullptr;
      copy(tree);
    }
    TwoThreeTree(two_three_tree_type &&tree):
      fakeNode_(static_cast< node_type* >(::operator new(sizeof(node_type)))),
      root_(tree.root_),
      compare_(Compare())
    {
      fakeNode_->first = root_;
      root_->parent = fakeNode_;
      tree.root_ = nullptr;
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
      return *this;
    }
    ~TwoThreeTree()
    {
      clear();
      ::operator delete(fakeNode_);
    }
    reference front()
    {
      return iterator(iterator::goDown(root_)).value;
    }
    const_reference front() const
    {
      return iterator(iterator::goDown(root_)).value;
    }
    iterator begin()
    {
      return iterator(iterator::goDown(root_));
    }
    const_iterator cbegin() const
    {
      return const_iterator(iterator::goDown(root_));
    }
    iterator end()
    {
      return iterator(nullptr);
    }
    const_iterator cend() const
    {
      return const_iterator(nullptr);
    }
    bool empty() const
    {
      return root_ == nullptr;
    }
    void clear() noexcept
    {
      free(root_);
      delete root_;
      root_ = nullptr;
    }
    iterator insert_after(const_iterator pos, const Key &k, const Value &v)
    {
      root_ = insert(pos.node_, k, v);
      pos++;
      return iterator(pos.node_);
    }
    template< class InputIt >
    iterator insert_after(const_iterator pos, InputIt first, InputIt last)
    {
      for (; first != last; first++)
      {
        root_ = insert(pos.node_, (*first).first, (*first).second);
        pos++;
      }
      return iterator(pos.node_);
    }
    template< class ... ArgsKey, class ... ArgsValue >
    iterator emplace_after(const_iterator pos, ArgsKey &&...argsKey, ArgsValue &&...argsValue)
    {
      return insert_after(pos, std::forward< Key >(Key(argsKey...)), std::forward< Value >(Value(argsValue...)));
    }
    void insert(const Key &k, const Value &v)
    {
      root_ = insert(root_, k, v);
    }
    iterator erase_after(const_iterator pos)
    {
      root_ = remove(pos.node_, pos.value_.first);
      pos++;
      return iterator(pos.node_);
    }
    iterator erase_after(const_iterator first, const_iterator last)
    {
      for (; first != last; first++)
      {
        erase_after(first);
      }
      return iterator(last.node_);
    }
    void push_front(const Key &key, const Value &value)
    {
      root_ = insert(key, value);
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
  private:
    node_type *fakeNode_;
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
      fakeNode_->first = root_;
      root_->parent = fakeNode_;
    }
    node_type *remove(node_type *p, Key k)
    {
      node_type *item = search(p, k);
      if (!item)
      {
        return p;
      }
      node_type *min = nullptr;
      if (item->key[0] == k)
      {
        min = iterator::goDown(item->second);
      }
      else
      {
        min = iterator::goDown(item->third);
      }
      if (min)
      {
        Key &z = (k == item->key[0]? item->key[0]: item->key[1]);
        std::swap(z, min->key[0]);
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
          parent->first->insert(parent->key[0]);
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
          parent->removeFromNode(parent->key[0]);
          delete first;
        }
        else if (second == node)
        {
          first->insert(parent->key[0]);
          parent->removeFromNode(parent->key[0]);
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
          second->insert(parent->key[1]);
          parent->third = nullptr;
          parent->removeFromNode(parent->key[1]);
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
          node->insert(parent->key[1]);
          if (second->size == 2)
          {
            parent->key[1] = second->key[1];
            second->removeFromNode(second->key[1]);
            node->first = second->third;
            second->third = nullptr;
            if (node->first != nullptr)
            {
              node->first->parent = node;
            }
          }
          else if (first->size == 2)
          {
            parent->key[1] = second->key[0];
            node->first = second->second;
            second->second = second->first;
            if (node->first != nullptr)
            {
              node->first->parent = node;
            }
            second->key[0] = parent->key[0];
            parent->key[0] = first->key[1];
            first->removeFromNode(first->key[1]);
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
            second->insert(parent->key[1]);
            parent->key[1] = third->key[0];
            third->removeFromNode(third->key[0]);
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
            second->insert(parent->key[0]);
            parent->key[0] = first->key[1];
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
          first->insert(parent->key[0]);
          if (second->size == 2)
          {
            parent->key[0] = second->key[0];
            second->removeFromNode(second->key[0]);
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
            parent->key[0] = second->key[0];
            second->key[0] = parent->key[1];
            parent->key[1] = third->key[0];
            third->removeFromNode(third->key[0]);
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
        node->insert(parent->key[0]);
        if (first == node && second->size == 2)
        {
          parent->key[0] = second->key[0];
          second->removeFromNode(second->key[0]);
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
          parent->key[0] = first->key[1];
          first->removeFromNode(first->key[1]);
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
        parent->second->insert(parent->key[0]);
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
        parent->removeFromNode(parent->key[0]);
        delete parent->first;
        parent->first = nullptr;
      }
      else if (parent->second == leaf)
      {
        parent->first->insert(parent->key[0]);
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
        parent->removeFromNode(parent->key[0]);
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
