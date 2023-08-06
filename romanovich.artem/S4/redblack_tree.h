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
    using data_type = std::pair< Key, Value >;
    using iterator = typename RotatableBinarySearchTree< Key, Value, Compare >::iterator;
    using const_iterator = typename RotatableBinarySearchTree< Key, Value, Compare >::const_iterator;
    RedBlackTree();
    RedBlackTree(const RedBlackTree &other);
    RedBlackTree(RedBlackTree &&other) noexcept;
    explicit RedBlackTree(const Compare &comp);
    template< typename InputIt >
    RedBlackTree(InputIt first, InputIt last, const Compare &comp = Compare());
    RedBlackTree(std::initializer_list< data_type > init, const Compare &comp = Compare());
    ~RedBlackTree() = default;
    RedBlackTree &operator=(const RedBlackTree &other);
    RedBlackTree &operator=(RedBlackTree &&other) noexcept;
    RedBlackTree &operator=(std::initializer_list< data_type > init);
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
    std::pair< iterator, bool > insert(const data_type value);
    template< typename P >
    std::pair< iterator, bool > insert(P &&value);
    iterator insert(const_iterator pos, const data_type value);
    template< typename P >
    iterator insert(const_iterator pos, P &&value);
    template< typename InputIt >
    void insert(InputIt first, InputIt last);
    void insert(std::initializer_list< data_type > init);
    template< typename... Args >
    std::pair< iterator, bool > emplace(Args &&... args);
    template< typename... Args >
    iterator emplace_hint(const_iterator hint, Args &&... args);
    data_type &at(const data_type &value);
    const data_type &at(const data_type &value) const;
    data_type &operator[](const data_type &value);
    data_type &operator[](data_type &&value);
    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    size_t erase(const data_type &value);
    void swap(RedBlackTree &other);
    size_t count(const data_type &value) const;
    iterator find(const data_type &value);
    const_iterator find(const data_type &value) const;
    std::pair< iterator, iterator > equal_range(const data_type &value);
    std::pair< const_iterator, const_iterator > equal_range(const data_type &value) const;
    iterator lower_bound(const data_type &value);
    const_iterator lower_bound(const data_type &value) const;
    iterator upper_bound(const data_type &value);
    const_iterator upper_bound(const data_type &value) const;
    Compare value_comp() const;
    bool equal(const RedBlackTree &rhs) const;
    void insert(const data_type &data);
    void remove(const data_type &data);
  private:
    RotatableBinarySearchTree< Key, Value, Compare > *rotBst_;
    void leftRotate(ColorTreeNode< data_type > *colorNode);
    void rightRotate(ColorTreeNode< data_type > *colorNode);
    void balanceAfterInsert(ColorTreeNode< data_type > *colorNode);
    void balanceAfterRemove(ColorTreeNode< data_type > *colorNode);
  };
  template< typename Key, typename Value, typename Compare >
  RedBlackTree< Key, Value, Compare >::RedBlackTree(const RedBlackTree &other)
  {
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::balanceAfterRemove(ColorTreeNode< data_type > *colorNode)
  {
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::balanceAfterInsert(ColorTreeNode< data_type > *colorNode)
  {
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::rightRotate(ColorTreeNode< data_type > *colorNode)
  {
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::leftRotate(ColorTreeNode< data_type > *colorNode)
  {
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::remove(const data_type &data)
  {
    ColorTreeNode< data_type > *node = findNode(data);
    //delete
    balanceAfterRemove(node);
  }
  template< typename Key, typename Value, typename Compare >
  void RedBlackTree< Key, Value, Compare >::insert(const data_type &data)
  {
    auto *newNode = new ColorTreeNode< data_type >(data);
    //insert
    balanceAfterInsert(newNode);
  }
  template< typename Key, typename Value, typename Compare >
  RedBlackTree< Key, Value, Compare >::RedBlackTree():
    rotBst_(nullptr)
  {
      rotBst_->bst_.fakeNode_ = ColorTreeNode< data_type>();
  }
}
#endif
