#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <utility>
#include <functional>
#include "tree_node.h"
#include "binary_search_tree.h"
#include "bidirectional_iterator.h"
#include "const_bidirectional_iterator.h"
template< typename Key, typename Value, typename Compare = std::less< Key >>
class RotatableBinarySearchTree
{
public:
  using data_type = std::pair< Key, Value >;
  using r_bst_t = RotatableBinarySearchTree< Key, Value, Compare >;
  using tree_t = TreeNode< data_type >;
  using iterator = typename BinarySearchTree< Key, Value, Compare >::iterator;
  using const_iterator = typename BinarySearchTree< Key, Value, Compare >::const_iterator;
  RotatableBinarySearchTree();
  RotatableBinarySearchTree(const RotatableBinarySearchTree &other) = default;
  RotatableBinarySearchTree(RotatableBinarySearchTree &&other) noexcept;
  explicit RotatableBinarySearchTree(const Compare &comp);
  template< typename InputIt >
  RotatableBinarySearchTree(InputIt first, InputIt last, const Compare &comp = Compare());
  RotatableBinarySearchTree(std::initializer_list< data_type > init, const Compare &comp = Compare());
  ~RotatableBinarySearchTree() = default;
  RotatableBinarySearchTree &operator=(const RotatableBinarySearchTree &other);
  RotatableBinarySearchTree &operator=(RotatableBinarySearchTree &&other) noexcept;
  RotatableBinarySearchTree &operator=(std::initializer_list< data_type > init);
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
  std::pair< iterator, bool > insert(const data_type &value);
  template< typename P >
  std::pair< iterator, bool > insert(P &&value);
  iterator insert(const_iterator pos, const data_type &value);
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
  void swap(RotatableBinarySearchTree &other);
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
  bool isEqual(const RotatableBinarySearchTree &rhs) const;
private:
  BinarySearchTree< Key, Value, Compare > bst_;
};
#endif
