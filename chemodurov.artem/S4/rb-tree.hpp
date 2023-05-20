#ifndef S4_RB_TREE_HPP
#define S4_RB_TREE_HPP
#include "rotatable-binary-search-tree.hpp"

namespace chemodurov
{
  template< typename T, typename Compare >
  class RBTree
  {
   public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_compare = Compare;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = typename RotatableBinarySearchTree< value_type, value_compare >::iterator;
    using const_iterator = typename RotatableBinarySearchTree< value_type, value_compare >::const_iterator;
    using this_t = RBTree< value_type, value_compare >;
    RBTree();
    RBTree(const this_t & other) = default;
    RBTree(this_t && other) noexcept;
    explicit RBTree(const value_compare & comp);
    template< typename InputIt >
    RBTree(InputIt first, InputIt last, const value_compare & comp = value_compare());
    RBTree(std::initializer_list< value_type > init, const value_compare & comp = value_compare());
    ~RBTree() = default;
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
    RotatableBinarySearchTree< T, Compare > data;
  };

  template< typename T, typename Compare >
  RBTree< T, Compare >::RBTree():
    data()
  {}

  template< typename T, typename Compare >
  RBTree< T, Compare >::RBTree(this_t && other) noexcept:
    data(std::move(other.data))
  {}

  template< typename T, typename Compare >
  RBTree< T, Compare >::RBTree(const value_compare & comp):
    data(comp)
  {}

  template< typename T, typename Compare >
  template< typename InputIt >
  RBTree< T, Compare >::RBTree(InputIt first, InputIt last, const value_compare & comp):
    data(first, last, comp)
  {}

  template< typename T, typename Compare >
  RBTree< T, Compare >::RBTree(std::initializer_list< value_type > init, const value_compare & comp):
    data(init, comp)
  {}

  template< typename T, typename Compare >
  RBTree< T, Compare > & RBTree< T, Compare >::operator=(const this_t & other)
  {
    data = other.data;
    return *this;
  }

  template< typename T, typename Compare >
  RBTree< T, Compare > & RBTree< T, Compare >::operator=(this_t && other) noexcept
  {
    data = std::move(other.data);
    return *this;
  }

  template< typename T, typename Compare >
  RBTree< T, Compare > & RBTree< T, Compare >::operator=(std::initializer_list< value_type > init)
  {
    data = init;
    return *this;
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::begin() noexcept
  {
    return data.begin();
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_iterator RBTree< T, Compare >::begin() const noexcept
  {
    return data.begin();
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_iterator RBTree< T, Compare >::cbegin() const noexcept
  {
    return data.cbegin();
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::end() noexcept
  {
    return data.end();
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_iterator RBTree< T, Compare >::end() const noexcept
  {
    return data.end();
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_iterator RBTree< T, Compare >::cend() const noexcept
  {
    return data.cend();
  }

  template< typename T, typename Compare >
  bool RBTree< T, Compare >::empty() const noexcept
  {
    return data.empty();
  }

  template< typename T, typename Compare >
  size_t RBTree< T, Compare >::size() const noexcept
  {
    return data.size();
  }

  template< typename T, typename Compare >
  void RBTree< T, Compare >::clear() noexcept
  {
    data.clear();
  }

  template< typename T, typename Compare >
  std::pair<
      typename RBTree< T, Compare >::iterator,
      bool
  > RBTree< T, Compare >::insert(const_reference value)
  {
    return data.insert(value);
  }

  template< typename T, typename Compare >
  template< typename P >
  std::pair<
      typename RBTree< T, Compare >::iterator,
      bool
  > RBTree< T, Compare >::insert(P && value)
  {
    return data.insert(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::insert(const_iterator pos, const_reference value)
  {
    return data.insert(pos, value);
  }

  template< typename T, typename Compare >
  template< typename P >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::insert(const_iterator pos, P && value)
  {
    return data.insert(pos, value);
  }

  template< typename T, typename Compare >
  template< typename InputIt >
  void RBTree< T, Compare >::insert(InputIt first, InputIt last)
  {
    data.insert(first, last);
  }

  template< typename T, typename Compare >
  void RBTree< T, Compare >::insert(std::initializer_list< value_type > init)
  {
    data.insert(init);
  }

  template< typename T, typename Compare >
  template< typename... Args >
  std::pair<
      typename RBTree< T, Compare >::iterator,
      bool
  > RBTree< T, Compare >::emplace(Args && ... args)
  {
    return data.emplace(std::forward< Args >(args)...);
  }

  template< typename T, typename Compare >
  template< typename... Args >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::emplace_hint(const_iterator hint, Args && ... args)
  {
    return data.emplace_hint(hint, std::forward< Args >(args)...);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::reference RBTree< T, Compare >::at(const_reference value)
  {
    return data.at(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_reference RBTree< T, Compare >::at(const_reference value) const
  {
    return data.at(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::reference RBTree< T, Compare >::operator[](const_reference value)
  {
    return data[value];
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::reference RBTree< T, Compare >::operator[](value_type && value)
  {
    return data[std::move(value)];
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::erase(iterator pos)
  {
    return data.erase(pos);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::erase(const_iterator pos)
  {
    return data.erase(pos);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::erase(const_iterator first, const_iterator last)
  {
    return data.erase(first, last);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::size_type RBTree< T, Compare >::erase(const_reference value)
  {
    return data.erase(value);
  }

  template< typename T, typename Compare >
  void RBTree< T, Compare >::swap(this_t & other)
  {
    data.swap(other.data);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::size_type RBTree< T, Compare >::count(const_reference value) const
  {
    return data.count(value);
  }
  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::find(const_reference value)
  {
    return data.find(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_iterator RBTree< T, Compare >::find(const_reference value) const
  {
    return data.find(value);
  }

  template< typename T, typename Compare >
  std::pair<
    typename RBTree< T, Compare >::iterator,
    typename RBTree< T, Compare >::iterator
  > RBTree< T, Compare >::equal_range(const_reference value)
  {
    return data.equal_range(value);
  }

  template< typename T, typename Compare >
  std::pair<
    typename RBTree< T, Compare >::const_iterator,
    typename RBTree< T, Compare >::const_iterator
  > RBTree< T, Compare >::equal_range(const_reference value) const
  {
    return data.equal_range(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::lower_bound(const_reference value)
  {
    return data.lower_bound(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_iterator RBTree< T, Compare >::lower_bound(const_reference value) const
  {
    return data.lower_bound(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::iterator RBTree< T, Compare >::upper_bound(const_reference value)
  {
    return data.upper_bound(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::const_iterator RBTree< T, Compare >::upper_bound(const_reference value) const
  {
    return data.upper_bound(value);
  }

  template< typename T, typename Compare >
  typename RBTree< T, Compare >::value_compare RBTree< T, Compare >::value_comp() const
  {
    return data.value_comp();
  }
}

#endif
