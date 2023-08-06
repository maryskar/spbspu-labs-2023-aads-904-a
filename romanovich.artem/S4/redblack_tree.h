#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H
#include "color_tree_node.h"
#include "rotatable_binary_search_tree.h"
namespace romanovich
{
  namespace details
  {
  }
  template< typename Key, typename Value, typename Compare = std::less<> >
  class RedBlackTree
  {
  public:
    using data_t = std::pair< Key, Value >;
    using iterator = typename RotatableBinarySearchTree< Key, Value, Compare >::iterator;
    using const_iterator = typename RotatableBinarySearchTree< Key, Value, Compare >::const_iterator;
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
    iterator last() noexcept;
    const_iterator last() const noexcept;
    const_iterator clast() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear() noexcept;
    std::pair< iterator, bool > insert(const data_t value);
    template< typename P >
    std::pair< iterator, bool > insert(P &&value);
    iterator insert(const_iterator pos, const data_t value);
    template< typename P >
    iterator insert(const_iterator pos, P &&value);
    template< typename InputIt >
    void insert(InputIt first, InputIt last);
    void insert(std::initializer_list< data_t > init);
    template< typename... Args >
    std::pair< iterator, bool > emplace(Args &&... args);
    template< typename... Args >
    iterator emplace_hint(const_iterator hint, Args &&... args);
    data_t &at(const data_t &value);
    const data_t &at(const data_t &value) const;
    data_t &operator[](const data_t &value);
    data_t &operator[](data_t &&value);
    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    size_t erase(const data_t &value);
    void swap(RedBlackTree &other);
    size_t count(const data_t &value) const;
    iterator find(const data_t &value);
    const_iterator find(const data_t &value) const;
    std::pair< iterator, iterator > equal_range(const data_t &value);
    std::pair< const_iterator, const_iterator > equal_range(const data_t &value) const;
    iterator lower_bound(const data_t &value);
    const_iterator lower_bound(const data_t &value) const;
    iterator upper_bound(const data_t &value);
    const_iterator upper_bound(const data_t &value) const;
    Compare value_comp() const;
    bool equal(const RedBlackTree &rhs) const;
    void insert(const data_t &data);
    void remove(const data_t &data);
  private:
    RotatableBinarySearchTree< Key, Value, Compare > rotBst_;
    void balanceAfterInsert(ColorTreeNode <data_t> *operationNode);
    void balanceAfterRemove(ColorTreeNode <data_t> *operationNode);
    void initColor();
  };
  template< typename Key, typename Value, typename Compare >
  std::pair<
    typename RedBlackTree< Key, Value, Compare >::iterator,
    bool
  > RedBlackTree< Key, Value, Compare >::insert(const RedBlackTree::data_t data)
  {
    auto *newNode = new TreeNode< data_t >(data);

    // Insert the new node into the underlying binary search tree
    auto insertionResult = rotBst_.insert(newNode);
    if (!insertionResult.second)
    {
      // The value already exists in the tree, so clean up and return the existing node
      delete newNode;
      return std::make_pair(insertionResult.first, false);
    }

    // Balance the tree after insert
    balanceAfterInsert(newNode);
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
    rotBst_->bst_.fakeNode_->color = Color::C_BLACK;
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
  void RedBlackTree< Key, Value, Compare >::balanceAfterRemove(ColorTreeNode <data_t> *operationNode)
  {
    while (operationNode != rotBst_.root() && operationNode->color == Color::C_BLACK)
    {
      if (operationNode == operationNode->parent->left)
      {
        ColorTreeNode <data_t> *sibling = operationNode->parent->right;

        if (sibling->color == Color::C_RED)
        {
          // Case 1: Sibling is red
          sibling->color = Color::C_BLACK;
          operationNode->parent->color = Color::C_RED;
          rotBst_.rotateLeftLeft(operationNode->parent);
          sibling = operationNode->parent->right;
        }

        if (sibling->left->color == Color::C_BLACK && sibling->right->color == Color::C_BLACK)
        {
          // Case 2: Sibling and its children are black
          sibling->color = Color::C_RED;
          operationNode = operationNode->parent;
        }
        else
        {
          if (sibling->right->color == Color::C_BLACK)
          {
            // Case 3: Sibling is black, sibling's left child is red, and sibling's right child is black
            sibling->left->color = Color::C_BLACK;
            sibling->color = Color::C_RED;
            rotBst_.rotateRightRight(sibling);
            sibling = operationNode->parent->right;
          }

          // Case 4: Sibling is black, sibling's right child is red
          sibling->color = operationNode->parent->color;
          operationNode->parent->color = Color::C_BLACK;
          sibling->right->color = Color::C_BLACK;
          rotBst_.rotateLeftLeft(operationNode->parent);
          operationNode = rotBst_.root();
        }
      }
      else
      {
        // Symmetric cases with "left" and "right" exchanged
        ColorTreeNode <data_t> *sibling = operationNode->parent->left;

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
  void RedBlackTree< Key, Value, Compare >::balanceAfterInsert(ColorTreeNode <data_t> *operationNode)
  {
    // Re-color and rotate as necessary to maintain Red-Black Tree properties
    while (operationNode->parent && operationNode->parent->color == Color::C_RED)
    {
      if (operationNode->parent == operationNode->parent->parent->left)
      {
        ColorTreeNode <data_t> *uncle = operationNode->parent->parent->right;
        if (uncle && uncle->color == Color::C_RED)
        {
          // Case 1: Recolor
          operationNode->parent->color = Color::C_BLACK;
          uncle->color = Color::C_BLACK;
          operationNode->parent->parent->color = Color::C_RED;
          operationNode = operationNode->parent->parent;
        }
        else
        {
          if (operationNode == operationNode->parent->right)
          {
            // Case 2: Left rotate and continue to case 3
            operationNode = operationNode->parent;
            rotBst_.rotateLeftLeft(operationNode);
          }
          // Case 3: Right rotate
          operationNode->parent->color = Color::C_BLACK;
          operationNode->parent->parent->color = Color::C_RED;
          rotBst_.rotateRightRight(operationNode->parent->parent);
        }
      }
      else
      {
        // Symmetric cases with "left" and "right" exchanged
        ColorTreeNode <data_t> *uncle = operationNode->parent->parent->left;
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

    // Ensure the root node is black
    rotBst_.root()->color = Color::C_BLACK;
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::remove(const data_t &data)
  {
    ColorTreeNode <data_t> *node = findNode(data);
    //delete
    balanceAfterRemove(node);
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::insert(const data_t &data)
  {
    auto *newNode = new ColorTreeNode< data_t >(data);
    //insert
    balanceAfterInsert(newNode);
  }
}
#endif
