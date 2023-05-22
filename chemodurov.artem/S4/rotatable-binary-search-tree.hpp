#ifndef S4_ROTATABLE_BINARY_SEARCH_TREE_HPP
#define S4_ROTATABLE_BINARY_SEARCH_TREE_HPP
#include "unbalanced-binary-search-tree.hpp"

namespace chemodurov
{
  template< typename T, typename Compare >
  class RBTree;

  template< typename T, typename Compare >
  class RotatableBinarySearchTree
  {
    friend class RBTree< T, Compare >;
   public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_compare = Compare;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = typename UnbalancedBinarySearchTree< value_type, value_compare >::iterator;
    using const_iterator = typename UnbalancedBinarySearchTree< value_type, value_compare >::const_iterator;
    using this_t = RotatableBinarySearchTree< value_type, value_compare >;
    RotatableBinarySearchTree();
    RotatableBinarySearchTree(const this_t & other) = default;
    RotatableBinarySearchTree(this_t && other) noexcept;
    explicit RotatableBinarySearchTree(const value_compare & comp);
    template< typename InputIt >
    RotatableBinarySearchTree(InputIt first, InputIt last, const value_compare & comp = value_compare());
    RotatableBinarySearchTree(std::initializer_list< value_type > init, const value_compare & comp = value_compare());
    ~RotatableBinarySearchTree() = default;
    this_t & operator=(const this_t & other);
    this_t & operator=(this_t && other) noexcept;
    this_t & operator=(std::initializer_list< value_type > init);
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear() noexcept;
    std::pair< iterator, bool > insert(const_reference value);
    template< typename P >
    std::pair< iterator, bool > insert(P && value);
    iterator insert(const_iterator pos, const_reference value);
    template< typename P >
    iterator insert(const_iterator pos, P && value);
    template< typename InputIt >
    void insert(InputIt first, InputIt last);
    void insert(std::initializer_list< value_type > init);
    template< typename... Args >
    std::pair< iterator, bool > emplace(Args && ... args);
    template< typename... Args >
    iterator emplace_hint(const_iterator hint, Args && ... args);
    reference at(const_reference value);
    const_reference at(const_reference value) const;
    reference operator[](const_reference value);
    reference operator[](value_type && value);
    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    size_type erase(const_reference value);
    void swap(this_t & other);
    size_type count(const_reference value) const;
    iterator find(const_reference value);
    const_iterator find(const_reference value) const;
    std::pair< iterator, iterator > equal_range(const_reference value);
    std::pair< const_iterator, const_iterator > equal_range(const_reference value) const;
    iterator lower_bound(const_reference value);
    const_iterator lower_bound(const_reference value) const;
    iterator upper_bound(const_reference value);
    const_iterator upper_bound(const_reference value) const;
    value_compare value_comp() const;
   private:
    UnbalancedBinarySearchTree< T, Compare > data_;
    void rotateLeftLeft(Tree< T, Compare > * to_rotate);
    void rotateRightRight(Tree< T, Compare > * to_rotate);
  };

  template< typename T, typename Compare >
  RotatableBinarySearchTree< T, Compare >::RotatableBinarySearchTree():
   data_()
  {}

  template< typename T, typename Compare >
  RotatableBinarySearchTree< T, Compare >::RotatableBinarySearchTree(this_t && other) noexcept:
   data_(std::move(other.data))
  {}

  template< typename T, typename Compare >
  RotatableBinarySearchTree< T, Compare >::RotatableBinarySearchTree(const value_compare & comp):
   data_(comp)
  {}

  template< typename T, typename Compare >
  template< typename InputIt >
  RotatableBinarySearchTree< T, Compare >::RotatableBinarySearchTree(InputIt first, InputIt last, const value_compare & comp):
   data_(first, last, comp)
  {}

  template< typename T, typename Compare >
  RotatableBinarySearchTree< T, Compare >::RotatableBinarySearchTree(std::initializer_list< value_type > init,
      const value_compare & comp):
   data_(init, comp)
  {}

  template< typename T, typename Compare >
  RotatableBinarySearchTree< T, Compare > & RotatableBinarySearchTree< T, Compare >::operator=(const this_t & other)
  {
    data_ = other.data;
    return *this;
  }

  template< typename T, typename Compare >
  RotatableBinarySearchTree< T, Compare > & RotatableBinarySearchTree< T, Compare >::operator=(this_t && other) noexcept
  {
    data_ = std::move(other.data);
    return *this;
  }

  template< typename T, typename Compare >
  RotatableBinarySearchTree< T, Compare > &
      RotatableBinarySearchTree< T, Compare >::operator=(std::initializer_list< value_type > init)
  {
    data_ = init;
    return *this;
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::iterator
      RotatableBinarySearchTree< T, Compare >::begin() noexcept
  {
    return data_.begin();
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::const_iterator
      RotatableBinarySearchTree< T, Compare >::begin() const noexcept
  {
    return data_.begin();
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::const_iterator
      RotatableBinarySearchTree< T, Compare >::cbegin() const noexcept
  {
    return data_.cbegin();
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::iterator
      RotatableBinarySearchTree< T, Compare >::end() noexcept
  {
    return data_.end();
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::const_iterator
      RotatableBinarySearchTree< T, Compare >::end() const noexcept
  {
    return data_.end();
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::const_iterator
      RotatableBinarySearchTree< T, Compare >::cend() const noexcept
  {
    return data_.cend();
  }

  template< typename T, typename Compare >
  bool RotatableBinarySearchTree< T, Compare >::empty() const noexcept
  {
    return data_.empty();
  }

  template< typename T, typename Compare >
  size_t RotatableBinarySearchTree< T, Compare >::size() const noexcept
  {
    return data_.size();
  }

  template< typename T, typename Compare >
  void RotatableBinarySearchTree< T, Compare >::clear() noexcept
  {
    data_.clear();
  }

  template< typename T, typename Compare >
  std::pair<
      typename RotatableBinarySearchTree< T, Compare >::iterator,
      bool
  > RotatableBinarySearchTree< T, Compare >::insert(const_reference value)
  {
    return data_.insert(value);
  }

  template< typename T, typename Compare >
  template< typename P >
  std::pair<
      typename RotatableBinarySearchTree< T, Compare >::iterator,
      bool
  > RotatableBinarySearchTree< T, Compare >::insert(P && value)
  {
    return data_.insert(value);
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::iterator
      RotatableBinarySearchTree< T, Compare >::insert(const_iterator pos, const_reference value)
  {
    return data_.insert(pos, value);
  }

  template< typename T, typename Compare >
  template< typename P >
  typename RotatableBinarySearchTree< T, Compare >::iterator
      RotatableBinarySearchTree< T, Compare >::insert(const_iterator pos, P && value)
  {
    return data_.insert(pos, value);
  }

  template< typename T, typename Compare >
  template< typename InputIt >
  void RotatableBinarySearchTree< T, Compare >::insert(InputIt first, InputIt last)
  {
    data_.insert(first, last);
  }

  template< typename T, typename Compare >
  void RotatableBinarySearchTree< T, Compare >::insert(std::initializer_list< value_type > init)
  {
    data_.insert(init);
  }

  template< typename T, typename Compare >
  template< typename... Args >
  std::pair<
      typename RotatableBinarySearchTree< T, Compare >::iterator,
      bool
  > RotatableBinarySearchTree< T, Compare >::emplace(Args && ... args)
  {
    return data_.emplace(std::forward< Args >(args)...);
  }

  template< typename T, typename Compare >
  template< typename... Args >
  typename RotatableBinarySearchTree< T, Compare >::iterator
      RotatableBinarySearchTree< T, Compare >::emplace_hint(const_iterator hint, Args && ... args)
  {
    return data_.emplace_hint(hint, std::forward< Args >(args)...);
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::reference
      RotatableBinarySearchTree< T, Compare >::at(const_reference value)
  {
    return data_.at(value);
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::const_reference
      RotatableBinarySearchTree< T, Compare >::at(const_reference value) const
  {
    return data_.at(value);
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::reference
      RotatableBinarySearchTree< T, Compare >::operator[](const_reference value)
  {
    return data_[value];
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::reference
      RotatableBinarySearchTree< T, Compare >::operator[](value_type && value)
  {
    return data_[std::move(value)];
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::iterator
      RotatableBinarySearchTree< T, Compare >::erase(iterator pos)
  {
    return data_.erase(pos);
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::iterator
      RotatableBinarySearchTree< T, Compare >::erase(const_iterator pos)
  {
    return data_.erase(pos);
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::iterator
      RotatableBinarySearchTree< T, Compare >::erase(const_iterator first, const_iterator last)
  {
    return data_.erase(first, last);
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::size_type
      RotatableBinarySearchTree< T, Compare >::erase(const_reference value)
  {
    return data_.erase(value);
  }

  template< typename T, typename Compare >
  void RotatableBinarySearchTree< T, Compare >::swap(this_t & other)
  {
    data_.swap(other.data_);
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::size_type
      RotatableBinarySearchTree< T, Compare >::count(const_reference value) const
  {
    return data_.count(value);
  }
  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::iterator
      RotatableBinarySearchTree< T, Compare >::find(const_reference value)
  {
    return data_.find(value);
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::const_iterator
      RotatableBinarySearchTree< T, Compare >::find(const_reference value) const
  {
    return data_.find(value);
  }

  template< typename T, typename Compare >
  std::pair<
      typename RotatableBinarySearchTree< T, Compare >::iterator,
      typename RotatableBinarySearchTree< T, Compare >::iterator
  > RotatableBinarySearchTree< T, Compare >::equal_range(const_reference value)
  {
    return data_.equal_range(value);
  }

  template< typename T, typename Compare >
  std::pair<
      typename RotatableBinarySearchTree< T, Compare >::const_iterator,
      typename RotatableBinarySearchTree< T, Compare >::const_iterator
  > RotatableBinarySearchTree< T, Compare >::equal_range(const_reference value) const
  {
    return data_.equal_range(value);
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::iterator
      RotatableBinarySearchTree< T, Compare >::lower_bound(const_reference value)
  {
    return data_.lower_bound(value);
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::const_iterator
      RotatableBinarySearchTree< T, Compare >::lower_bound(const_reference value) const
  {
    return data_.lower_bound(value);
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::iterator
      RotatableBinarySearchTree< T, Compare >::upper_bound(const_reference value)
  {
    return data_.upper_bound(value);
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::const_iterator
      RotatableBinarySearchTree< T, Compare >::upper_bound(const_reference value) const
  {
    return data_.upper_bound(value);
  }

  template< typename T, typename Compare >
  typename RotatableBinarySearchTree< T, Compare >::value_compare
      RotatableBinarySearchTree< T, Compare >::value_comp() const
  {
    return data_.value_comp();
  }

  template< typename T, typename Compare >
  void RotatableBinarySearchTree< T, Compare >::rotateLeftLeft(Tree< T, Compare > * to_rotate)
  {
    to_rotate->parent_->right_ = to_rotate->left_;
    if (to_rotate->left_ != data_.fake_)
    {
      to_rotate->left_->parent_ = to_rotate->parent_;
    }
    to_rotate->left_ = to_rotate->parent_;
    to_rotate->parent_ = to_rotate->parent_->parent_;
    to_rotate->left_->parent_ = to_rotate;
    if (to_rotate->parent_ == data_.fake_)
    {
      to_rotate->parent_->left_ = to_rotate;
    }
    else
    {
      to_rotate->parent_->left_ == to_rotate->left_ ? to_rotate->parent_->left_ = to_rotate : to_rotate->parent_->right_ = to_rotate;
    }
  }

  template< typename T, typename Compare >
  void RotatableBinarySearchTree< T, Compare >::rotateRightRight(Tree< T, Compare > * to_rotate)
  {
    to_rotate->parent_->left_ = to_rotate->right_;
    if (to_rotate->right_ != data_.fake_)
    {
      to_rotate->right_->parent_ = to_rotate->parent_;
    }
    to_rotate->right_ = to_rotate->parent_;
    to_rotate->parent_ = to_rotate->right_->parent_;
    to_rotate->right_->parent_ = to_rotate;
    if (to_rotate->parent_ == data_.fake_)
    {
      to_rotate->parent_->left_ = to_rotate;
    }
    else
    {
      to_rotate->parent_->left_ == to_rotate->right_ ? to_rotate->parent_->left_ = to_rotate : to_rotate->parent_->right_ = to_rotate;
    }
  }
}

#endif
