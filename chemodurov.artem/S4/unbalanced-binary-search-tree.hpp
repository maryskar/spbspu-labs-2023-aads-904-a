#ifndef S4_UNBALANCED_BINARY_SEARCH_TREE_HPP
#define S4_UNBALANCED_BINARY_SEARCH_TREE_HPP
#include <functional>
#include "bidirectional-iterator.hpp"

namespace chemodurov
{
  template< typename T, typename Compare = std::less< > >
  class UnbalancedBinarySearchTree
  {
    friend class BidirectionalIterator< T, Compare >;
   public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_compare = Compare;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = BidirectionalIterator< value_type, value_compare >;
    using const_iterator = ConstBidirectionalIterator< value_type, value_compare >;
    using this_t = UnbalancedBinarySearchTree< value_type, value_compare >;
    UnbalancedBinarySearchTree();
    UnbalancedBinarySearchTree(const this_t & other);
    UnbalancedBinarySearchTree(this_t && other);
    UnbalancedBinarySearchTree(const value_compare & comp);
    template< typename InputIt >
    UnbalancedBinarySearchTree(InputIt first, InputIt last, const value_compare & comp = value_compare());
    UnbalancedBinarySearchTree(std::initializer_list< value_type > init, const value_compare & comp = value_compare());
    ~UnbalancedBinarySearchTree();
    this_t & operator=(const this_t & other);
    this_t & operator=(this_t && other);
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
    template < typename... Args >
    iterator emplace_hint(const_iterator hint, Args && ... args);
    T& at( const_reference value );
    const T& at( const_reference value ) const;
    T& operator[]( const_reference value );
    T& operator[]( value_type && value );
    iterator erase( iterator pos );
    iterator erase( const_iterator pos );
    iterator erase( const_iterator first, const_iterator last );
    size_type erase( const_reference value );
    void swap(this_t & other);
    size_type count( const_reference value ) const;
    iterator find( const_reference value );
    const_iterator find( const_reference value ) const;
    std::pair<iterator,iterator> equal_range( const_reference value );
    std::pair<const_iterator,const_iterator> equal_range( const_reference value ) const;
    iterator lower_bound( const_reference value);
    const_iterator lower_bound( const_reference value ) const;
    iterator upper_bound( const_reference value );
    const_iterator upper_bound( const_reference value ) const;
    value_compare value_comp() const;
   private:
    Tree< T, Compare > * fake_;
    Compare comp_;
    std::size_t size_;
  };

  template< typename T, typename Compare >
  UnbalancedBinarySearchTree< T, Compare >::UnbalancedBinarySearchTree():
   fake_(::operator new (sizeof(Tree< T, Compare >))),
   comp_(),
   size_(0)
  {
    fake_->left_ = nullptr;
    fake_->right_ = fake_;
    fake_->parent_ = fake_;
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator UnbalancedBinarySearchTree< T, Compare >::begin() noexcept
  {
    return iterator(fake_->parent_, fake_);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::const_iterator UnbalancedBinarySearchTree< T, Compare >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::const_iterator UnbalancedBinarySearchTree< T, Compare >::cbegin() const noexcept
  {
    return const_iterator(fake_->parent_, fake_);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::iterator UnbalancedBinarySearchTree< T, Compare >::end() noexcept
  {
    return iterator(fake_, fake_);
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::const_iterator UnbalancedBinarySearchTree< T, Compare >::end() const noexcept
  {
    return cend();
  }

  template< typename T, typename Compare >
  typename UnbalancedBinarySearchTree< T, Compare >::const_iterator UnbalancedBinarySearchTree< T, Compare >::cend() const noexcept
  {
    return const_iterator(fake_, fake_);
  }

  template< typename T, typename Compare >
  bool UnbalancedBinarySearchTree< T, Compare >::empty() const noexcept
  {
    return !size_;
  }

  template< typename T, typename Compare >
  size_t UnbalancedBinarySearchTree< T, Compare >::size() const noexcept
  {
    return size_;
  }

  template< typename T, typename Compare >
  void clearTree(Tree< T, Compare > * root, Tree< T, Compare > * fake)
  {
    if (root == fake)
    {
      return;
    }
    clearTree(root->left_, fake);
    clearTree(root->right_, fake);
    delete root;
  }

  template< typename T, typename Compare >
  void UnbalancedBinarySearchTree< T, Compare >::clear() noexcept
  {
    clearTree(fake_->left_, fake_);
  }
}

#endif
