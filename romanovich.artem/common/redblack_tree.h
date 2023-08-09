#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H
#include "tree_node.h"
#include "rotatable_binary_search_tree.h"
namespace romanovich
{
  template< typename Key, typename Value, typename Compare = std::less<> >
  class RedBlackTree
  {
  public:
    using data_t = std::pair< Key, Value >;
    using iterator = typename RotatableBinarySearchTree< Key, Value, Compare >::iterator;
    using const_iterator = typename RotatableBinarySearchTree< Key, Value, Compare >::const_iterator;
    using reverse_iterator = std::reverse_iterator< iterator >;
    using const_reverse_iterator = std::reverse_iterator< const_iterator >;
    RedBlackTree();
    RedBlackTree(const RedBlackTree &other);
    RedBlackTree(RedBlackTree &&other) noexcept;
    explicit RedBlackTree(const Compare &compare);
    ~RedBlackTree() = default;
    template< typename InputIt >
    RedBlackTree(InputIt first, InputIt last, const Compare &compare = Compare());
    RedBlackTree(std::initializer_list< data_t > init, const Compare &compare = Compare());
    RedBlackTree &operator=(const RedBlackTree &other);
    RedBlackTree &operator=(RedBlackTree &&other) noexcept;
    RedBlackTree &operator=(std::initializer_list< data_t > init);
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    iterator last() noexcept;
    const_iterator last() const noexcept;
    const_iterator clast() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear() noexcept;
    std::pair< iterator, bool > insert(const data_t &data);
    template< typename P >
    std::pair< iterator, bool > insert(P &&data);
    iterator insert(const_iterator pos, const data_t &value);
    template< typename P >
    iterator insert(const_iterator pos, P &&data);
    template< typename InputIt >
    void insert(InputIt first, InputIt last);
    void insert(std::initializer_list< data_t > init);
    template< typename... Args >
    std::pair< iterator, bool > emplace(Args &&... args);
    Value &at(const Key &key);
    const Value &at(const Key &key) const;
    Value &operator[](const Key &key);
    Value &operator[](Key &&key);
    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    size_t erase(const Key &key);
    void swap(RedBlackTree &other);
    size_t count(const Key &key) const;
    iterator find(const Key &key);
    const_iterator find(const Key &key) const;
    iterator lower_bound(const Key &key);
    const_iterator lower_bound(const Key &key) const;
    iterator upper_bound(const Key &key);
    const_iterator upper_bound(const Key &key) const;
    Compare value_comp() const;
    bool equal(const RedBlackTree &rhs) const;
    void remove(const data_t &data);
    template< typename F >
    void traverseLnr(F &f) const;
    template< typename F >
    void traverseRnl(F &f) const;
    template< typename F >
    void traverseBreadth(F &f) const;
  private:
    void balanceAfterInsert(TreeNode< data_t > *operationNode);
    void balanceAfterRemove(TreeNode< data_t > *operationNode);
    void initColor();
    RotatableBinarySearchTree< Key, Value, Compare > rotBst_;
  };
  template< typename Key, typename Value, typename Compare >
  template< typename F >
  void RedBlackTree< Key, Value, Compare >::traverseBreadth(F &f) const
  {
    rotBst_.traverseBreadth(f);
  }
  template< typename Key, typename Value, typename Compare >
  template< typename F >
  void RedBlackTree< Key, Value, Compare >::traverseRnl(F &f) const
  {
    rotBst_.traverseRnl(f);
  }
  template< typename Key, typename Value, typename Compare >
  template< typename F >
  void RedBlackTree< Key, Value, Compare >::traverseLnr(F &f) const
  {
    rotBst_.traverseLnr(f);
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::const_reverse_iterator
  RedBlackTree< Key, Value, Compare >::crend() const noexcept
  {
    return rotBst_.crend();
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::const_reverse_iterator
  RedBlackTree< Key, Value, Compare >::rend() const noexcept
  {
    return rotBst_.rend();
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::reverse_iterator
  RedBlackTree< Key, Value, Compare >::rend() noexcept
  {
    return rotBst_.rend();
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::const_reverse_iterator
  RedBlackTree< Key, Value, Compare >::crbegin() const noexcept
  {
    return rotBst_.crbegin();
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::const_reverse_iterator
  RedBlackTree< Key, Value, Compare >::rbegin() const noexcept
  {
    return rotBst_.rbegin();
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::reverse_iterator
  RedBlackTree< Key, Value, Compare >::rbegin() noexcept
  {
    return rotBst_.rbegin();
  }
  template< typename Key, typename Value, typename Compare >
  bool RedBlackTree< Key, Value, Compare >::equal(const RedBlackTree &rhs) const
  {
    return rotBst_ == rhs.rotBst_;
  }
  template< typename Key, typename Value, typename Compare >
  Compare RedBlackTree< Key, Value, Compare >::value_comp() const
  {
    return rotBst_.value_comp();
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::const_iterator
  RedBlackTree< Key, Value, Compare >::upper_bound(const Key &key) const
  {
    return rotBst_.upper_bound(key);
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::iterator
  RedBlackTree< Key, Value, Compare >::upper_bound(const Key &key)
  {
    return rotBst_.upper_bound(key);
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::const_iterator RedBlackTree< Key, Value, Compare >::lower_bound(
    const Key &key) const
  {
    return rotBst_.lower_bound(key);
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::iterator RedBlackTree< Key, Value, Compare >::lower_bound(
    const Key &key)
  {
    return rotBst_.lower_bound(key);
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::const_iterator
  RedBlackTree< Key, Value, Compare >::find(const Key &key) const
  {
    return rotBst_.find(key);
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::iterator
  RedBlackTree< Key, Value, Compare >::find(const Key &key)
  {
    return rotBst_.find(key);
  }
  template< typename Key, typename Value, typename Compare >
  size_t RedBlackTree< Key, Value, Compare >::count(const Key &key) const
  {
    return rotBst_.count(key);
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::swap(RedBlackTree &other)
  {
    rotBst_.swap(other.rotBst_);
  }
  template< typename Key, typename Value, typename Compare >
  size_t RedBlackTree< Key, Value, Compare >::erase(const Key &key)
  {
    const_iterator constIt = find(key);
    if (constIt != cend())
    {
      erase(constIt);
      return 1;
    }
    return 0;
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::iterator
  RedBlackTree< Key, Value, Compare >::erase(RedBlackTree::const_iterator first, RedBlackTree::const_iterator last)
  {
    while (first != last)
    {
      iterator it = erase(first++);
      balanceAfterRemove(it.node_);
    }
    return iterator(first.node_, rotBst_.bst_.fakeNode_);
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::iterator
  RedBlackTree< Key, Value, Compare >::erase(RedBlackTree::const_iterator pos)
  {
    iterator it = erase(pos);
    balanceAfterRemove(it.node_);
    return it;
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::iterator
  RedBlackTree< Key, Value, Compare >::erase(RedBlackTree::iterator pos)
  {
    iterator it = erase(const_iterator(pos));
    balanceAfterRemove(it.node_);
    return it;
  }
  template< typename Key, typename Value, typename Compare >
  Value &
  RedBlackTree< Key, Value, Compare >::operator[](Key &&key)
  {
    return (*this)[key];
  }
  template< typename Key, typename Value, typename Compare >
  Value &
  RedBlackTree< Key, Value, Compare >::operator[](const Key &key)
  {
    return rotBst_[key];
  }
  template< typename Key, typename Value, typename Compare >
  const Value &
  RedBlackTree< Key, Value, Compare >::at(const Key &key) const
  {
    return rotBst_.at(key);
  }
  template< typename Key, typename Value, typename Compare >
  Value &
  RedBlackTree< Key, Value, Compare >::at(const Key &key)
  {
    return rotBst_.at(key);
  }
  template< typename Key, typename Value, typename Compare >
  template< typename... Args >
  std::pair< typename RedBlackTree< Key, Value, Compare >::iterator, bool >
  RedBlackTree< Key, Value, Compare >::emplace(Args &&... args)
  {
    data_t tmp(std::forward< Args >(args)...);
    return insert(tmp);
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::insert(std::initializer_list< data_t > init)
  {
    insert(init.begin(), init.end());
  }
  template< typename Key, typename Value, typename Compare >
  template< typename InputIt >
  void RedBlackTree< Key, Value, Compare >::insert(InputIt first, InputIt last)
  {
    while (first != last)
    {
      insert(*first++);
    }
  }
  template< typename Key, typename Value, typename Compare >
  template< typename P >
  typename RedBlackTree< Key, Value, Compare >::iterator
  RedBlackTree< Key, Value, Compare >::insert(RedBlackTree::const_iterator pos, P &&data)
  {
    data_t tmp(data);
    return insert(pos, tmp);
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::iterator
  RedBlackTree< Key, Value, Compare >::insert(RedBlackTree::const_iterator pos, const data_t &value)
  {
    auto insertionResult = rotBst_.insert(pos, value);
    if (!insertionResult.second)
    {
      return insertionResult.first;
    }
    TreeNode< data_t > *newNode = insertionResult.first.node_;
    if (newNode->parent && newNode->parent->color == Color::C_RED)
    {
      balanceAfterInsert(newNode);
    }
    return insertionResult.first;
  }
  template< typename Key, typename Value, typename Compare >
  template< typename P >
  std::pair< typename RedBlackTree< Key, Value, Compare >::iterator,
    bool > RedBlackTree< Key, Value, Compare >::insert(P &&data)
  {
    const data_t tmp(data);
    return insert(tmp);
  }
  template< typename Key, typename Value, typename Compare >
  std::pair<
    typename RedBlackTree< Key, Value, Compare >::iterator,
    bool
  > RedBlackTree< Key, Value, Compare >::insert(const data_t &data)
  {
    auto insertionResult = rotBst_.insert(data);
    if (!insertionResult.second)
    {
      return std::make_pair(insertionResult.first, false);
    }
    balanceAfterInsert(insertionResult.first.node_);
    return std::make_pair(insertionResult.first, true);
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::clear() noexcept
  {
    rotBst_.clear();
  }
  template< typename Key, typename Value, typename Compare >
  size_t RedBlackTree< Key, Value, Compare >::size() const noexcept
  {
    return rotBst_.size();
  }
  template< typename Key, typename Value, typename Compare >
  bool RedBlackTree< Key, Value, Compare >::empty() const noexcept
  {
    return rotBst_.empty();
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::const_iterator
  RedBlackTree< Key, Value, Compare >::cend() const noexcept
  {
    return rotBst_.cend();
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::const_iterator RedBlackTree< Key, Value, Compare >::end() const noexcept
  {
    return rotBst_.end();
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::iterator RedBlackTree< Key, Value, Compare >::end() noexcept
  {
    return rotBst_.end();
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::const_iterator
  RedBlackTree< Key, Value, Compare >::clast() const noexcept
  {
    return rotBst_.clast();
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::const_iterator
  RedBlackTree< Key, Value, Compare >::last() const noexcept
  {
    return rotBst_.last();
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::iterator RedBlackTree< Key, Value, Compare >::last() noexcept
  {
    return rotBst_.last();
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::const_iterator
  RedBlackTree< Key, Value, Compare >::cbegin() const noexcept
  {
    return rotBst_.cbegin();
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::const_iterator
  RedBlackTree< Key, Value, Compare >::begin() const noexcept
  {
    return rotBst_.begin();
  }
  template< typename Key, typename Value, typename Compare >
  typename RedBlackTree< Key, Value, Compare >::iterator RedBlackTree< Key, Value, Compare >::begin() noexcept
  {
    return rotBst_.begin();
  }
  template< typename Key, typename Value, typename Compare >
  RedBlackTree< Key, Value, Compare > &
  RedBlackTree< Key, Value, Compare >::operator=(std::initializer_list< data_t > init)
  {
    RedBlackTree< Key, Value, Compare > tmp(init);
    swap(tmp);
    return *this;
  }
  template< typename Key, typename Value, typename Compare >
  RedBlackTree< Key, Value, Compare > &RedBlackTree< Key, Value, Compare >::operator=(RedBlackTree &&other) noexcept
  {
    if (this != std::addressof(other))
    {
      RedBlackTree< Key, Value, Compare > tmp(std::swap(other));
      clear();
      swap(tmp);
    }
    return *this;
  }
  template< typename Key, typename Value, typename Compare >
  RedBlackTree< Key, Value, Compare > &RedBlackTree< Key, Value, Compare >::operator=(const RedBlackTree &other)
  {
    if (this != std::addressof(other))
    {
      RedBlackTree< Key, Value, Compare > tmp(other);
      clear();
      swap(tmp);
    }
    return *this;
  }
  template< typename Key, typename Value, typename Compare >
  RedBlackTree< Key, Value, Compare >::RedBlackTree(std::initializer_list< data_t > init, const Compare &compare):
    RedBlackTree(init.begin(), init.end(), compare)
  {
  }
  template< typename Key, typename Value, typename Compare >
  RedBlackTree< Key, Value, Compare >::RedBlackTree(const Compare &compare):
    rotBst_(compare)
  {
    initColor();
  }
  template< typename Key, typename Value, typename Compare >
  template< typename InputIt >
  RedBlackTree< Key, Value, Compare >::RedBlackTree(InputIt first, InputIt last, const Compare &compare):
    RedBlackTree(compare)
  {
    insert(first, last);
  }
  template< typename Key, typename Value, typename Compare >
  RedBlackTree< Key, Value, Compare >::RedBlackTree(RedBlackTree &&other) noexcept:
    rotBst_(std::move(other.rotBst_))
  {
    initColor();
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::initColor()
  {
    rotBst_.bst_.fakeNode_->color = Color::C_BLACK;
  }
  template< typename Key, typename Value, typename Compare >
  RedBlackTree< Key, Value, Compare >::RedBlackTree():
    rotBst_()
  {
    initColor();
  }
  template< typename Key, typename Value, typename Compare >
  RedBlackTree< Key, Value, Compare >::RedBlackTree(const RedBlackTree &other):
    rotBst_(other.rotBst_)
  {
    initColor();
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::balanceAfterRemove(TreeNode< data_t > *operationNode)
  {
    while (operationNode != rotBst_.root() && operationNode->color == Color::C_BLACK)
    {
      if (operationNode == operationNode->parent->left)
      {
        TreeNode< data_t > *sibling = operationNode->parent->right;
        if (sibling->color == Color::C_RED)
        {
          sibling->color = Color::C_BLACK;
          operationNode->parent->color = Color::C_RED;
          rotBst_.rotateLeftLeft(operationNode->parent);
          sibling = operationNode->parent->right;
        }
        if (sibling->left->color == Color::C_BLACK && sibling->right->color == Color::C_BLACK)
        {
          sibling->color = Color::C_RED;
          operationNode = operationNode->parent;
        }
        else
        {
          if (sibling->right->color == Color::C_BLACK)
          {
            sibling->left->color = Color::C_BLACK;
            sibling->color = Color::C_RED;
            rotBst_.rotateRightRight(sibling);
            sibling = operationNode->parent->right;
          }
          sibling->color = operationNode->parent->color;
          operationNode->parent->color = Color::C_BLACK;
          sibling->right->color = Color::C_BLACK;
          rotBst_.rotateLeftLeft(operationNode->parent);
          operationNode = rotBst_.root();
        }
      }
      else
      {
        TreeNode< data_t > *sibling = operationNode->parent->left;
        if (sibling->color == Color::C_RED)
        {
          sibling->color = Color::C_BLACK;
          operationNode->parent->color = Color::C_RED;
          rotBst_.rotateRightRight(operationNode->parent);
          sibling = operationNode->parent->left;
        }
        if (sibling->left->color == Color::C_BLACK && sibling->right->color == Color::C_BLACK)
        {
          sibling->color = Color::C_RED;
          operationNode = operationNode->parent;
        }
        else
        {
          if (sibling->left->color == Color::C_BLACK)
          {
            sibling->right->color = Color::C_BLACK;
            sibling->color = Color::C_RED;
            rotBst_.rotateLeftLeft(sibling);
            sibling = operationNode->parent->left;
          }
          sibling->color = operationNode->parent->color;
          operationNode->parent->color = Color::C_BLACK;
          sibling->left->color = Color::C_BLACK;
          rotBst_.rotateRightRight(operationNode->parent);
          operationNode = rotBst_.root();
        }
      }
    }
    operationNode->color = Color::C_BLACK;
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::balanceAfterInsert(TreeNode< data_t > *operationNode)
  {
    while (operationNode->parent && operationNode->parent->color == Color::C_RED)
    {
      if (operationNode->parent == operationNode->parent->parent->left)
      {
        TreeNode< data_t > *uncle = operationNode->parent->parent->right;
        if (uncle && uncle->color == Color::C_RED)
        {
          operationNode->parent->color = Color::C_BLACK;
          uncle->color = Color::C_BLACK;
          operationNode->parent->parent->color = Color::C_RED;
          operationNode = operationNode->parent->parent;
        }
        else
        {
          if (operationNode == operationNode->parent->right)
          {
            operationNode = operationNode->parent;
            rotBst_.rotateLeftLeft(operationNode);
          }
          operationNode->parent->color = Color::C_BLACK;
          operationNode->parent->parent->color = Color::C_RED;
          rotBst_.rotateRightRight(operationNode->parent->parent);
        }
      }
      else
      {
        TreeNode< data_t > *uncle = operationNode->parent->parent->left;
        if (uncle && uncle->color == Color::C_RED)
        {
          operationNode->parent->color = Color::C_BLACK;
          uncle->color = Color::C_BLACK;
          operationNode->parent->parent->color = Color::C_RED;
          operationNode = operationNode->parent->parent;
        }
        else
        {
          if (operationNode == operationNode->parent->left)
          {
            operationNode = operationNode->parent;
            rotBst_.rotateRightRight(operationNode);
          }
          operationNode->parent->color = Color::C_BLACK;
          operationNode->parent->parent->color = Color::C_RED;
          rotBst_.rotateLeftLeft(operationNode->parent->parent);
        }
      }
    }
    rotBst_.bst_.root_->color = Color::C_BLACK;
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::remove(const data_t &data)
  {
    TreeNode< data_t > *node = findNode(data);
    balanceAfterRemove(node);
  }
}
#endif
