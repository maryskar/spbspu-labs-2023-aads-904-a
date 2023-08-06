#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H
#include "color_tree_node.h"
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
    RedBlackTree();
    RedBlackTree(const RedBlackTree &other);
    RedBlackTree(RedBlackTree &&other) noexcept;
    explicit RedBlackTree(const Compare &comp);
    template< typename InputIt >
    RedBlackTree(InputIt first, InputIt last, const Compare &comp = Compare());
    RedBlackTree(std::initializer_list< data_t > init, const Compare &comp = Compare());
    ~RedBlackTree() = default;
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
    RotatableBinarySearchTree< Key, Value, Compare > *rotBst_;
    void leftRotate(ColorTreeNode< data_t > *colorNode);
    void rightRotate(ColorTreeNode< data_t > *colorNode);
    void balanceAfterInsert(ColorTreeNode< data_t > *colorNode);
    void balanceAfterRemove(ColorTreeNode< data_t > *colorNode);
  };
  template< typename Key, typename Value, typename Compare >
  RedBlackTree< Key, Value, Compare >::RedBlackTree(const RedBlackTree &other)
  {
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::balanceAfterRemove(ColorTreeNode< data_t > *colorNode)
  {
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::balanceAfterInsert(ColorTreeNode< data_t > *colorNode)
  {
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::rightRotate(ColorTreeNode< data_t > *colorNode)
  {
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::leftRotate(ColorTreeNode< data_t > *colorNode)
  {
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::remove(const data_t &data)
  {
    ColorTreeNode< data_t > *node = findNode(data);
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
  template< typename Key, typename Value, typename Compare >
  RedBlackTree< Key, Value, Compare >::RedBlackTree():
    rotBst_(nullptr)
  {
      rotBst_->bst_.fakeNode_ = ColorTreeNode< data_t>();
  }
}
#endif
