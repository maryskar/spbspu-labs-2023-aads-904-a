#ifndef SPBSPU_LABS_2023_AADS_904_A_BINARYSEARCHTREE_H
#define SPBSPU_LABS_2023_AADS_904_A_BINARYSEARCHTREE_H
#include <cstddef>
#include <algorithm>
#include <iterator>
#include "nodeToInsert.h"
#include "nodeOfTwoThreeTree.h"
#include "nodeOfTwoThreeTreeOne.h"
#include "nodeOfTwoThreeTreeTwo.h"
#include "twoThreeTreeIterator.h"
#include "twoThreeTreeIteratorConst.h"
#include "twoThreeTreeReverseIterator.h"
#include "twoThreeTreeReverseIteratorConst.h"
#include "math_functions.h"
#include "stack.h"
#include "queue.h"
namespace dimkashelk
{
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTree
  {
  using node_to_insert = details::NodeToInsert< Key, Value >;
  using node_type = details::NodeOfTwoThreeTree< Key, Value >;
  using node_one_type = details::NodeOfTwoThreeTreeOne< Key, Value >;
  using node_two_type = details::NodeOfTwoThreeTreeTwo< Key, Value >;
  using two_three_tree_type = TwoThreeTree< Key, Value, Compare >;
  using reference = std::pair< const Key, Value >&;
  using const_reference = const reference&;
  friend class TwoThreeTreeIterator< Key, Value, Compare >;
  friend class TwoThreeTreeIteratorConst< Key, Value, Compare >;
  public:
    using iterator = dimkashelk::TwoThreeTreeIterator< Key, Value, Compare >;
    using const_iterator = dimkashelk::TwoThreeTreeIteratorConst< Key, Value, Compare >;
    using reverse_iterator = dimkashelk::TwoThreeTreeReverseIterator< Key, Value, Compare >;
    using const_reverse_iterator = dimkashelk::TwoThreeTreeReverseIteratorConst< Key, Value, Compare >;
    using key_type = const Key;
    using compare_type = Compare;
    TwoThreeTree():
      size_(0),
      was_updated_while_insert_(false),
      compare_(Compare()),
      to_insert_(nullptr),
      fakeNode_(static_cast< node_type * >(::operator new(sizeof(node_one_type)))),
      root_(nullptr)
    {}
    TwoThreeTree(const two_three_tree_type &tree):
      size_(0),
      was_updated_while_insert_(false),
      compare_(Compare()),
      to_insert_(nullptr),
      fakeNode_(static_cast< node_type * >(::operator new(sizeof(node_one_type)))),
      root_(copy(tree))
    {}
    TwoThreeTree(two_three_tree_type &&tree):
      size_(tree.size_),
      was_updated_while_insert_(false),
      compare_(Compare()),
      to_insert_(tree.to_insert_),
      fakeNode_(static_cast< node_type* >(::operator new(sizeof(node_one_type)))),
      root_(tree.root_)
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
        if (node->getSize() == 2)
        {
          auto *twoNode = node->getTwoNode();
          if (details::isEqual< Key, Compare >(k, twoNode->data[0].first))
          {
            return twoNode->data[0].second;
          }
          else if (details::isEqual< Key, Compare >(k, twoNode->data[1].first))
          {
            return twoNode->data[1].second;
          }
        }
        else
        {
          auto *oneNode = node->getOneNode();
          if (details::isEqual< Key, Compare >(k, oneNode->data.first))
          {
            return oneNode->data.second;
          }
        }
      }
      throw std::logic_error("No element");
    }
    bool contains(const Key &k) const
    {
      node_type *node = search(root_, k);
      return containsInNode(k, node);
    }
    template< typename F >
    F &traverse_lnr(F &f) const
    {
      if (empty())
      {
        throw std::logic_error("Empty tree");
      }
      Stack< std::pair< unsigned, node_type * > > nodeStack;
      node_type *node = root_;
      while (!nodeStack.empty() || node != nullptr)
      {
        if (node != nullptr)
        {
          nodeStack.pushFront({0, node});
          node = node->getFirstChild();
        }
        else
        {
          std::pair< unsigned, node_type * > &p = nodeStack.front();
          node = p.second;
          f(p.second->getData(p.first).second);
          if (p.second->getSize() == 2)
          {
            if (p.first == 0)
            {
              nodeStack.popFront();
              nodeStack.pushFront({1, node});
              node = node->getSecondChild();
              continue;
            }
            else
            {
              node = node->getThirdChild();
            }
          }
          else
          {
            node = node->getSecondChild();
          }
          nodeStack.popFront();
        }
      }
      return f;
    }
    template< typename F >
    F &traverse_rnl(F &f) const
    {
      if (empty())
      {
        throw std::logic_error("Empty tree");
      }
      Stack< std::pair< unsigned, node_type * > > nodeStack;
      node_type *node = root_;
      while (!nodeStack.empty() || node != nullptr)
      {
        if (node != nullptr)
        {
          nodeStack.pushFront(getPairTraverseRnl(node));
          node = node->getFirstChild();
        }
        else
        {
          std::pair< unsigned, node_type * > &p = nodeStack.front();
          node = p.second;
          f(p.second->getData(p.first).second);
          if (p.second->getSize() == 2)
          {
            if (p.first == 1)
            {
              nodeStack.popFront();
              nodeStack.pushFront({0, node});
              node = node->getSecondChild();
              continue;
            }
            else
            {
              node = node->getFirstChild();
            }
          }
          else
          {
            node = node->getFirstChild();
          }
          nodeStack.popFront();
        }
      }
      return f;
    }
    template< typename F >
    F &traverse_breadth(F &f) const
    {
      if (empty())
      {
        throw std::logic_error("Empty tree");
      }
      Queue< node_type * > queue;
      queue.push(root_);
      while (!queue.empty()) {
        node_type *node = queue.front();
        queue.popFront();
        if (node->getSize() == 2)
        {
          auto *twoNode = node->getTwoNode();
          f(twoNode->data[0]);
          f(twoNode->data[1]);
          addChildsToQueue(queue, twoNode);
        }
        else
        {
          auto *oneNode = node->getOneNode();
          f(oneNode->data);
          addChildsToQueue(queue, oneNode);
        }
      }
      return f;
    }
  private:
    size_t size_;
    bool was_updated_while_insert_;
    Compare compare_;
    node_to_insert *to_insert_;
    node_type *fakeNode_;
    node_type *root_;
    void addChildsToQueue(Queue< node_type * > &queue, node_two_type *node)
    {
      if (node->first)
      {
        queue.push(node->first);
      }
      if (node->second)
      {
        queue.push(node->second);
      }
      if (node->third)
      {
        queue.push(node->third);
      }
    }
    void addChildsToQueue(Queue< node_type * > &queue, node_one_type *node)
    {
      if (node->first)
      {
        queue.push(node->first);
      }
      if (node->second)
      {
        queue.push(node->second);
      }
    }
    std::pair< unsigned, node_type * > getPairTraverseRnl(node_type *node) const
    {
      if (node->getSize() == 2)
      {
        return {1, node};
      }
      else
      {
        return {0, node};
      }
    }
    node_type *getNewNodeFromLeftChild()
    {
      node_type *new_node = new node_type(to_insert_->data[0].first, to_insert_->data[0].second);
      new_node->setFirstChild(to_insert_->first);
      new_node->setSecondChild(to_insert_->second);
      new_node->setParent(to_insert_->parent);
      return new_node;
    }
    node_type *getNewNodeFromRightChild()
    {
      node_type *new_node = new node_type(to_insert_->data[2].first, to_insert_->data[2].second);
      new_node->setFirstChild(to_insert_->first);
      new_node->setSecondChild(to_insert_->third);
      new_node->setParent(to_insert_->fourth);
      return new_node;
    }
    bool containsInNode(const Key &k, const node_type *node) const
    {
      if (node->getSize() == 1)
      {
        return details::isEqual< Key, Compare >(k, node->getOneNode()->data.first);
      }
      auto *twoNode = node->getTwoNode();
      bool isEqualFirst = details::isEqual< Key, Compare >(k, twoNode->data[0].first);
      bool isEqualSecond = details::isEqual< Key, Compare >(k, twoNode->data[1].first);
      return isEqualFirst || isEqualSecond;
    }
    node_to_insert *generateNodeToInsert(node_type *p, const Key &k, const Value &v)
    {
      if (p->getSize() != 2)
      {
        throw std::logic_error("Doesn't need to create, check");
      }
      node_to_insert *toInsert = nullptr;
      std::pair< const Key, Value > data = {k, v};
      if (compare_(k, p->getData(0).first))
      {
        toInsert = new node_to_insert(data, p->getData(0), p->getData(1), p);
      }
      else if (compare_(k, p->getData(1).first))
      {
        toInsert = new node_to_insert(p->getData(0), data, p->getData(1), p);
      }
      else
      {
        toInsert = new node_to_insert(p->getData(0), p->getData(1), data, p);
      }
      return toInsert;
    }
    node_type *insert(node_type *p, const Key &k, const Value &v)
    {
      if (!p)
      {
        return new node_type(k, v);
      }
      if (containsInNode(k, p))
      {
        if (details::isEqual< Key, Compare >(p->getData(0).first, k))
        {
          p->getData(0).second = v;
        }
        else if (details::isEqual< Key, Compare >(p->getData(1).first, k))
        {
          p->getData(1).second = v;
        }
        was_updated_while_insert_ = true;
        return p;
      }
      if (p->isList())
      {
        if (p->getSize() < 2)
        {
          if (compare_(k, p->getData(0).first))
          {
            p->insertFront(k, v);
          }
          else
          {
            p->insert(k, v);
          }
          return p;
        }
        else
        {
          if (to_insert_)
          {
            delete to_insert_;
          }
          to_insert_ = generateNodeToInsert(p, k, v);
        }
      }
      else if (compare_(k, p->getData(0).first))
      {
        insert(p->getFirstChild(), k, v);
      }
      else if (((p->getSize() == 1) || ((p->getSize() == 2) && compare_(k, p->getData(1).first))))
      {
        insert(p->getSecondChild(), k, v);
      }
      else
      {
        insert(p->getThirdChild(), k, v);
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
      if (x->getFirstChild())
      {
        x->getFirstChild()->setParent(x);
      }
      if (x->getSecondChild())
      {
        x->getSecondChild()->setParent(x);
      }
      if (y->getFirstChild())
      {
        y->getFirstChild()->setParent(y);
      }
      if (y->getSecondChild())
      {
        y->getSecondChild()->setParent(y);
      }
      if (to_insert_->parent)
      {
        auto *parent = to_insert_->parent;
        if (parent->getSize() == 2)
        {
          node_to_insert *new_node = generateNodeToInsert(parent, to_insert_->data[1].first, to_insert_->data[1].second);
          if (details::isEqual< Key, Compare >(new_node->data[0].first, to_insert_->data[1].first))
          {
            new_node->first = x;
            new_node->second = y;
            new_node->third = item->getFirstChild();
            new_node->fourth = item->getSecondChild();
          }
          else if (details::isEqual< Key, Compare >(new_node->data[1].first, to_insert_->data[1].first))
          {
            new_node->first = item->getFirstChild();
            new_node->second = x;
            new_node->third = y;
            new_node->fourth = item->getSecondChild();
          }
          else if (details::isEqual< Key, Compare >(new_node->data[2].first, to_insert_->data[1].first))
          {
            new_node->first = item->getFirstChild();
            new_node->second = item->getSecondChild();
            new_node->third = x;
            new_node->fourth = y;
          }
          delete to_insert_;
          to_insert_ = new_node;
        }
        else
        {
          if (compare_(parent->getData(0).first, to_insert_->data[1].first))
          {
            parent->insert(to_insert_->data[1].first, to_insert_->data[1].second);
          }
          else
          {
            parent->insertFront(to_insert_->data[1].first, to_insert_->data[1].second);
          }
          if (parent->getFirstChild() == item)
          {
            parent->setThirdChild(item->getParent()->getSecondChild());
            parent->setSecondChild(y);
            parent->setFirstChild(x);
          }
          else if (parent->getSecondChild() == item)
          {
            item->getParent()->setThirdChild(y);
            item->getParent()->setSecondChild(x);
            delete item;
          }
          delete to_insert_;
          to_insert_ = nullptr;
        }
      }
      else
      {
        node_type *parent = new node_type(to_insert_->data[1].first, to_insert_->data[1].second);
        parent->setFirstChild(x);
        parent->setSecondChild(y);
        x->setParent(parent);
        y->setParent(parent);
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
      if (containsInNode(k, node))
      {
        return node;
      }
      else if (compare_(k, node->getData(0).first))
      {
        return search(node->getFirstChild(), k);
      }
      else if ((node->getSize() == 2 && compare_(k, node->getData(1).first)) || node->getSize() == 1)
      {
        return search(node->getSecondChild(), k);
      }
      else if (node->getSize() == 2)
      {
        return search(node->getThirdChild(), k);
      }
      return nullptr;
    }
    void free(node_type *node)
    {
      if (node == nullptr)
      {
        return;
      }
      if (node->getLastChild() == nullptr)
      {
        return;
      }
      free(node->getFirstChild());
      delete node->getFirstChild();
      node->setFirstChild(nullptr);
      free(node->getSecondChild());
      delete node->getSecondChild();
      node->setSecondChild(nullptr);
      if (node->getSize() == 2)
      {
        free(node->getThirdChild());
        delete node->getThirdChild();
        node->setThirdChild(nullptr);
      }
    }
    node_type *copy(const two_three_tree_type &tree)
    {
      size_ = 0;
      root_ = nullptr;
      for (auto iter = tree.cbegin(); iter != tree.cend(); iter++)
      {
        insert(iter->first, iter->second);
      }
      return root_;
    }
    void removeFromNode(node_type *node, const Key &k)
    {
      if (details::isEqual< Key, Compare >(node->getData(0).first, k))
      {
        node->removeFirst();
      }
      else if (node->getSize() == 2 && details::isEqual< Key, Compare >(node->getData(1).first, k))
      {
        node->removeSecond();
      }
    }
    node_type *remove(node_type *p, const Key &k)
    {
      node_type *item = search(p, k);
      if (!item)
      {
        return p;
      }
      node_type *min = nullptr;
      if (details::isEqual< Key, Compare >(item->getData(0).first, k))
      {
        min = iterator::goDown(item->getSecondChild());
      }
      else
      {
        min = iterator::goDown(item->getThirdChild());
      }
      if (min)
      {
        reference z = (details::isEqual< Key, Compare >(k, item->getData(0).first)? item->getData(0): item->getData(1));
        std::swap(z, min->getData(0));
        item = min;
      }
      removeFromNode(item, k);
      return fix(item);
    }
    node_type *fix(node_type *leaf)
    {
      if (leaf->getSize() == 0 && leaf->getParent() == nullptr)
      {
        delete leaf;
        return nullptr;
      }
      if (leaf->getSize() != 0)
      {
        if (leaf->getParent())
        {
          return fix(leaf->getParent());
        }
        else
        {
          return leaf;
        }
      }
      node_type *parent = leaf->getParent();
      if (parent->getFirstChild()->getParent() == 2 || parent->getSecondChild()->getSize() == 2 || parent->getSize() == 2)
      {
        leaf = rebalance(leaf);
      }
      else if (parent->getSize() == 2 && parent->getThirdChild()->getSize() == 2)
      {
        leaf = rebalance(leaf);
      }
      else
      {
        leaf = merge(leaf);
      }
      return fix(leaf);
    }
    node_type *copyPointers(node_type *copy_in, node_type *from_copy)
    {
      copy_in->setParent(from_copy->getParent());
      copy_in->setFirstChild(from_copy->getFirstChild());
      copy_in->setSecondChild(from_copy->getSecondChild());
      copy_in->setThirdChild(from_copy->getThirdChild());
      return copy_in;
    }
    node_type *copyBegin(node_type *to_copy, node_type *from_copy)
    {
      node_type *new_node = new node_type(to_copy->getData(0).first, to_copy->getData(0).second);
      new_node->insert(from_copy->getData(0).first, from_copy->getData(0).second);
      return copyPointers(new_node, to_copy);
    }
    node_type *copyInBeginBegin(node_type *to_copy, node_type *from_copy)
    {
      node_type *new_node = new node_type(from_copy->getData(0).first, from_copy->getData(0).second);
      new_node->insert(to_copy->getData(1).first, to_copy->getData(1).second);
      return copyPointers(new_node, to_copy);
    }
    node_type *copyEnd(node_type *to_copy, node_type *from_copy)
    {
      node_type *new_node = new node_type(to_copy->getData(0).first, to_copy->getData(0).second);
      new_node->insert(from_copy->getData(1).first, from_copy->getData(1).second);
      return copyPointers(new_node, to_copy);
    }
    node_type *copyInBeginEnd(node_type *to_copy, node_type *from_copy)
    {
      node_type *new_node = new node_type(from_copy->getData(0).first, to_copy->getData(0).second);
      new_node->insert(to_copy->getData(1).first, to_copy->getData(1).second);
      return copyPointers(new_node, to_copy);
    }
    node_type *copyInEndBegin(node_type *to_copy, node_type *from_copy)
    {
      node_type *new_node = new node_type(from_copy->getData(1).first, to_copy->getData(1).second);
      new_node->insert(to_copy->getData(1).first, to_copy->getData(1).second);
      return copyPointers(new_node, to_copy);
    }
    node_type *rebalance(node_type *node)
    {
      node_type *parent = node->getParent();
      node_type *first = parent->getFirstChild();
      node_type *second = parent->getSecondChild();
      node_type *third = parent->getThirdChild();
      if ((parent->getSize() == 2) && (first->getSize() < 2) && (second->getSize() < 2) && (third->getSize() < 2))
      {
        if (first == node)
        {
          parent->setFirstChild(parent->getSecondChild());
          parent->setSecondChild(parent->getThirdChild());
          parent->setThirdChild(nullptr);
          parent->getFirstChild()->insert(parent->data[0].first, parent->data[0].second);
          parent->getFirstChild()->setThirdChild(parent->getFirstChild()->getSecondChild());
          parent->getFirstChild()->setSecondChild(parent->getFirstChild()->getFirstChild());
          if (node->getFirstChild() != nullptr)
          {
            parent->getFirstChild()->setFirstChild(node->getFirstChild());
          }
          else if (node->getSecondChild() != nullptr)
          {
            parent->getFirstChild()->setFirstChild(node->getSecondChild());
          }
          if (parent->getFirstChild()->getFirstChild() != nullptr)
          {
            parent->getFirstChild()->getFirstChild()->setParent(parent->getFirstChild());
          }
          removeFromNode(parent, parent->getData(0).first);
          delete first;
        }
        else if (second == node)
        {
          first->insert(parent->data[0].first, parent->data[0].second);
          removeFromNode(parent, parent->getData(0).first);
          if (node->getFirstChild() != nullptr)
          {
            first->setThirdChild(node->first);
          }
          else if (node->getSecondChild() != nullptr)
          {
            first->setThirdChild(node->getSecondChild());
          }
          if (first->getThirdChild() != nullptr)
          {
            first->getThirdChild()->setParent(first);
          }
          parent->setSecondChild(parent->getThirdChild());
          parent->become2Node();
          delete second;
        }
        else if (third == node)
        {
          second->insert(parent->getData(1).first, parent->getData(1).second);
          parent->become2Node();
          if (node->getFirstChild() != nullptr)
          {
            second->setThirdChild(node->getFirstChild());
          }
          else if (node->getSecondChild() != nullptr)
          {
            second->setThirdChild(node->getSecondChild());
          }
          if (second->getThirdChild() != nullptr)
          {
            second->getThirdChild()->setParent(second);
          }
          delete third;
        }
      }
      else if ((parent->getSize() == 2) && ((first->getSize() == 2) || (second->getSize() == 2) || (third->getSize() == 2)))
      {
        if (third == node)
        {
          if (node->getFirstChild() != nullptr)
          {
            node->getSecondChild(node->first);
            node->getFirstChild(nullptr);
          }
          node->insert(parent->getData(1).first, parent->getData(1).second);
          if (second->getSize() == 2)
          {
            auto *new_parent = copyEnd(parent, second);
            delete parent;
            parent = new_parent;
            removeFromNode(second, second->data[1].first);
            node->setFirstChild(second->getThirdChild());
            second->become2Node();
            if (node->getFirstChild() != nullptr)
            {
              node->getFirstChild()->setParent(node);
            }
          }
          else if (first->getSize() == 2)
          {
            auto *res = copyBegin(parent, second);
            delete parent;
            parent = res;
            node->setFirstChild(second->getSecondChild());
            second->setSecondChild(second->getFirstChild());
            if (node->getFirstChild() != nullptr)
            {
              node->getFirstChild()->setParent(node);
            }
            res = copyInBeginBegin(second, parent);
            delete second;
            second = res;
            res = copyInEndBegin(parent, first);
            delete parent;
            parent = res;
            removeFromNode(first, first->data[1].first);
            second->setFirstChild(first->getThirdChild());
            first->become2Node();
            if (second->getFirstChild() != nullptr)
            {
              second->getFirstChild()->setParent(second);
            }
          }
        }
        else if (second == node)
        {
          if (third->getSize() == 2)
          {
            if (node->getFirstChild() == nullptr)
            {
              node->setFirstChild(node->getSecondChild());
              node->setSecondChild(nullptr);
            }
            second->insert(parent->getData(1).first, parent->getData(1).second);
            auto *res = copyBegin(parent, third);
            delete parent;
            parent = res;
            removeFromNode(third, third->getData(0).first);
            second->setSecondChild(third->getFirstChild());
            if (second->getSecondChild() != nullptr)
            {
              second->getSecondChild()->setParent(second);
            }
            third->setFirstChild(third->getSecondChild());
            third->setSecondChild(third->getThirdChild());
            third->become2Node();
          }
          else if (first->getSize() == 2)
          {
            if (node->getSecondChild() == nullptr)
            {
              node->setSecondChild(node->getFirstChild());
              node->setFirstChild(nullptr);
            }
            second->insert(parent->getData(0).first, parent->getData(0).second);
            auto *res = copyInEndBegin(parent, first);
            delete parent;
            parent = res;
            first->removeFromNode(first->getData(1).first);
            second->setFirstChild(first->getThirdChild());
            if (second->getFirstChild() != nullptr)
            {
              second->getFirstChild()->setParent(second);
            }
            first->become2Node();
          }
        }
        else if (first == node)
        {
          if (node->getFirstChild() == nullptr)
          {
            node->setFirstChild(node->getSecondChild());
            node->setSecondChild(nullptr);
          }
          first->insert(parent->getData(0).first, parent->getData(0).second);
          if (second->getSize() == 2)
          {
            auto *res = copyInBeginBegin(parent, second);
            delete parent;
            parent = res;
            removeFromNode(second, second->getData(0).first);
            first->setSecondChild(second->getFirstChild());
            if (first->getSecondChild() != nullptr)
            {
              first->getSecondChild()->setParent(first);
            }
            second->setFirstChild(second->getSecondChild());
            second->setSecondChild(second->getThirdChild());
            second->become2Node();
          }
          else if (third->getSize() == 2)
          {
            auto *res = copyInBeginBegin(parent, second);
            delete parent;
            parent = res;
            res = copyInEndBegin(second, parent);
            delete second;
            second = res;
            res = copyBegin(parent, third);
            delete parent;
            parent = res;
            removeFromNode(third, third->getData(0).first);
            first->setSecondChild(second->getFirstChild());
            if (first->getSecondChild() != nullptr)
            {
              first->getSecondChild()->setParent(first);
            }
            second->setFirstChild(second->getSecondChild());
            second->setSecondChild(third->getFirstChild());
            if (second->getSecondChild() != nullptr)
            {
              second->getSecondChild()->setParent(second);
            }
            third->setFirstChild(third->getSecondChild());
            third->setSecondChild(third->getThirdChild());
            third->become2Node();
          }
        }
      }
      else if (parent->getSize() == 1)
      {
        node->insert(parent->getData(0).first, parent->getData(0).second);
        if (first == node && second->getSize() == 2)
        {
          auto *res = copyInBeginBegin(parent, second);
          delete parent;
          parent = res;
          removeFromNode(second, second->getData(0).first);
          if (node->getFirstChild() == nullptr)
          {
            node->setFirstChild(node->getSecondChild());
          }
          node->setSecondChild(second->getFirstChild());
          second->setFirstChild(second->getSecondChild());
          second->setSecondChild(second->getThirdChild());
          second->become2Node();
          if (node->getSecondChild() != nullptr)
          {
            node->getSecondChild()->setParent(node);
          }
        }
        else if (second == node && first->getSize() == 2)
        {
          auto *res = copyInEndBegin(parent, first);
          delete parent;
          parent = first;
          removeFromNode(first, first->getData(1).first);
          if (node->getSecondChild() == nullptr)
          {
            node->setSecondChild(node->getFirstChild());
          }
          node->setFirstChild(first->getThirdChild());
          first->become2Node();
          if (node->getFirstChild() != nullptr)
          {
            node->getFirstChild()->setParent(node);
          }
        }
      }
      return parent;
    }
    node_type *merge(node_type *leaf)
    {
      node_type *parent = leaf->getParent();
      if (parent->getFirstChild() == leaf)
      {
        parent->getSecondChild()->insert(parent->getData(0).first, parent->getData(0).second);
        parent->getSecondChild()->setThirdChild(parent->getSecondChild()->getSecondChild());
        parent->getSecondChild()->setSecondChild(parent->getSecondChild()->getFirstChild());
        if (leaf->getFirstChild() != nullptr)
        {
          parent->getSecondChild()->setFirstChild(leaf->getFirstChild());
        }
        else if (leaf->getSecondChild() != nullptr)
        {
          parent->getSecondChild()->setFirstChild(leaf->getSecondChild());
        }
        if (parent->getSecondChild()->getFirstChild() != nullptr)
        {
          parent->getSecondChild()->getFirstChild()->setParent(parent->getSecondChild());
        }
        removeFromNode(parent, parent->getData(0).first);
        delete parent->getFirstChild();
        parent->setFirstChild(nullptr);
      }
      else if (parent->getSecondChild() == leaf)
      {
        parent->getFirstChild()->insert(parent->getData(0).first, parent->getData(0).second);
        if (leaf->getFirstChild() != nullptr)
        {
          parent->getFirstChild()->setThirdChild(leaf->getFirstChild());
        }
        else if (leaf->getSecondChild() != nullptr)
        {
          parent->getFirstChild()->setThirdChild(leaf->getSecondChild());
        }
        if (parent->getFirstChild()->getThirdChild() != nullptr)
        {
          parent->getFirstChild()->getThirdChild()->setParent(parent->getFirstChild());
        }
        removeFromNode(parent, parent->getData(0).first);
        delete parent->getSecondChild();
        parent->setSecondChild(nullptr);
      }
      if (parent->getParent() == nullptr)
      {
        node_type *tmp = nullptr;
        if (parent->getFirstChild() != nullptr)
        {
          tmp = parent->getFirstChild();
        }
        else
        {
          tmp = parent->getSecondChild();
        }
        tmp->setParent(nullptr);
        delete parent;
        return tmp;
      }
      return parent;
    }
  };
}
#endif
