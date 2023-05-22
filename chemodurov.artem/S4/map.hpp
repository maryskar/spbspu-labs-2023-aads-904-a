#ifndef S4_MAP_HPP
#define S4_MAP_HPP
#include "rb-tree.hpp"

namespace chemodurov
{
  template< typename Key, typename Value, typename Compare = std::less< > >
  class Map
  {
   public:
    class value_compare;
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair< const key_type, mapped_type >;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using key_compare = Compare;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = typename RBTree< value_type, value_compare >::iterator;
    using const_iterator = typename RBTree< value_type, value_compare >::const_iterator;
    using this_t = Map< key_type, mapped_type , key_compare >;
    Map();
    Map(const this_t & other) = default;
    Map(this_t && other) noexcept;
    explicit Map(const key_compare & comp);
    template< typename InputIt >
    Map(InputIt first, InputIt last, const key_compare & comp = key_compare());
    Map(std::initializer_list< value_type > init, const key_compare & comp = key_compare());
    ~Map() = default;
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
    mapped_type & at(const key_type & key);
    const mapped_type & at(const key_type & key) const;
    mapped_type & operator[](const key_type & key);
    mapped_type & operator[](key_type && key);
    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    size_type erase(const key_type & key);
    void swap(this_t & other);
    size_type count(const key_type & key) const;
    iterator find(const key_type & key);
    const_iterator find(const key_type & key) const;
    std::pair< iterator, iterator > equal_range(const key_type & key);
    std::pair< const_iterator, const_iterator > equal_range(const key_type & key) const;
    iterator lower_bound(const key_type & key);
    const_iterator lower_bound(const key_type & key) const;
    iterator upper_bound(const key_type & key);
    const_iterator upper_bound(const key_type & key) const;
    key_compare key_comp() const;
    value_compare value_comp() const;
    bool isEqual(const this_t & rhs);
   private:
    RBTree< value_type, value_compare > data_;
    key_compare comp_;
  };

  template< typename Key, typename Value, typename Compare >
  Map< Key, Value, Compare >::Map():
   data_(),
   comp_()
  {}

  template< typename Key, typename Value, typename Compare >
  Map< Key, Value, Compare >::Map(this_t && other) noexcept:
   data_(std::move(other.data_)),
   comp_(std::move(other.comp_))
  {}

  template< typename Key, typename Value, typename Compare >
  Map< Key, Value, Compare >::Map(const key_compare & comp):
   data_(value_compare(comp)),
   comp_(comp)
  {}

  template< typename Key, typename Value, typename Compare >
  template< typename InputIt >
  Map< Key, Value, Compare >::Map(InputIt first, InputIt last, const key_compare & comp):
   data_(first, last, value_compare(comp)),
   comp_(comp)
  {}

  template< typename Key, typename Value, typename Compare >
  Map< Key, Value, Compare >::Map(std::initializer_list< value_type > init, const key_compare & comp):
   data_(init, value_compare(comp)),
   comp_(comp)
  {}

  template< typename Key, typename Value, typename Compare >
  Map< Key, Value, Compare > & Map< Key, Value, Compare >::operator=(const this_t & other)
  {
    if (this == std::addressof(other))
    {
      return *this;
    }
    key_compare temp(other.comp_);
    data_ = other.data_;
    comp_ = std::move(temp);
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  Map< Key, Value, Compare > & Map< Key, Value, Compare >::operator=(this_t && other) noexcept
  {
    if (this == std::addressof(other))
    {
      return *this;
    }
    data_ = std::move(other.data_);
    comp_ = std::move(other.comp_);
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  Map< Key, Value, Compare > & Map< Key, Value, Compare >::operator=(std::initializer_list< value_type > init)
  {
    data_ = init;
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::iterator Map< Key, Value, Compare >::begin() noexcept
  {
    return data_.begin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::const_iterator Map< Key, Value, Compare >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::const_iterator Map< Key, Value, Compare >::cbegin() const noexcept
  {
    return data_.cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::iterator Map< Key, Value, Compare >::end() noexcept
  {
    return data_.end();
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::const_iterator Map< Key, Value, Compare >::end() const noexcept
  {
    return cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::const_iterator Map< Key, Value, Compare >::cend() const noexcept
  {
    return data_.cend();
  }
}

#endif
