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
    iterator last() noexcept;
    const_iterator last() const noexcept;
    const_iterator clast() const noexcept;
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
   data_(value_compare{}),
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
  typename Map< Key, Value, Compare >::iterator Map< Key, Value, Compare >::last() noexcept
  {
    return data_.last();
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::const_iterator Map< Key, Value, Compare >::last() const noexcept
  {
    return clast();
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::const_iterator Map< Key, Value, Compare >::clast() const noexcept
  {
    return data_.clast();
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

  template< typename Key, typename Value, typename Compare >
  bool Map< Key, Value, Compare >::empty() const noexcept
  {
    return data_.empty();
  }

  template< typename Key, typename Value, typename Compare >
  size_t Map< Key, Value, Compare >::size() const noexcept
  {
    return data_.size();
  }

  template< typename Key, typename Value, typename Compare >
  void Map< Key, Value, Compare >::clear() noexcept
  {
    data_.clear();
  }

  template< typename Key, typename Value, typename Compare >
  std::pair<
      typename Map< Key, Value, Compare >::iterator,
      bool
  > Map< Key, Value, Compare >::insert(const value_type & value)
  {
    return data_.insert(value);
  }

  template< typename Key, typename Value, typename Compare >
  template< typename P >
  std::pair<
      typename Map< Key, Value, Compare >::iterator,
      bool
  > Map< Key, Value, Compare >::insert(P && value)
  {
    return data_.insert(value);
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::iterator
      Map< Key, Value, Compare >::insert(const_iterator pos, const_reference value)
  {
    return data_.insert(pos, value);
  }

  template< typename Key, typename Value, typename Compare >
  template< typename P >
  typename Map< Key, Value, Compare >::iterator
      Map< Key, Value, Compare >::insert(const_iterator pos, P && value)
  {
    return data_.insert(pos, value);
  }

  template< typename Key, typename Value, typename Compare >
  template< typename InputIt >
  void Map< Key, Value, Compare >::insert(InputIt first, InputIt last)
  {
    data_.insert(first, last);
  }

  template< typename Key, typename Value, typename Compare >
  void Map< Key, Value, Compare >::insert(std::initializer_list< value_type > init)
  {
    data_.insert(init);
  }

  template< typename Key, typename Value, typename Compare >
  template< typename... Args >
  std::pair<
      typename Map< Key, Value, Compare >::iterator,
      bool
  > Map< Key, Value, Compare >::emplace(Args && ... args)
  {
    return data_.emplace(std::forward< Args >(args)...);
  }

  template< typename Key, typename Value, typename Compare >
  template< typename... Args >
  typename Map< Key, Value, Compare >::iterator
      Map< Key, Value, Compare >::emplace_hint(const_iterator hint, Args && ... args)
  {
    return data_.emplace_hint(hint, std::forward< Args >(args)...);
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::mapped_type & Map< Key, Value, Compare >::at(const key_type & key)
  {
    return const_cast< mapped_type & >((static_cast< const this_t & >(*this)).at(key));
  }

  template< typename Key, typename Value, typename Compare >
  const typename Map< Key, Value, Compare >::mapped_type & Map< Key, Value, Compare >::at(const key_type & key) const
  {
    return (data_.at({key, mapped_type{}})).second;
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::mapped_type & Map< Key, Value, Compare >::operator[](const key_type & key)
  {
    return data_[{key, mapped_type{}}];
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::mapped_type & Map< Key, Value, Compare >::operator[](key_type && key)
  {
    return (*this)[key];
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::iterator Map< Key, Value, Compare >::erase(iterator pos)
  {
    return data_.erase(pos);
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::iterator Map< Key, Value, Compare >::erase(const_iterator pos)
  {
    return data_.erase(pos);
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::iterator
      Map< Key, Value, Compare >::erase(const_iterator first, const_iterator last)
  {
    return data_.erase(first, last);
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::size_type Map< Key, Value, Compare >::erase(const key_type & key)
  {
    return data_.erase({key, mapped_type{}});
  }

  template< typename Key, typename Value, typename Compare >
  void Map< Key, Value, Compare >::swap(this_t & other)
  {
    std::swap(comp_, other.comp_);
    data_.swap(other.data_);
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::size_type Map< Key, Value, Compare >::count(const key_type & key) const
  {
    return data_.count({key, mapped_type{}});
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::iterator Map< Key, Value, Compare >::find(const key_type & key)
  {
    return data_.find({key, mapped_type{}});
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::const_iterator Map< Key, Value, Compare >::find(const key_type & key) const
  {
    return data_.find({key, mapped_type{}});
  }

  template< typename Key, typename Value, typename Compare >
  std::pair<
    typename Map< Key, Value, Compare >::iterator,
    typename Map< Key, Value, Compare >::iterator
  > Map< Key, Value, Compare >::equal_range(const key_type & key)
  {
    return data_.equal_range({key, mapped_type{}});
  }

  template< typename Key, typename Value, typename Compare >
  std::pair<
      typename Map< Key, Value, Compare >::const_iterator,
      typename Map< Key, Value, Compare >::const_iterator
  > Map< Key, Value, Compare >::equal_range(const key_type & key) const
  {
    return data_.equal_range({key, mapped_type{}});
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::iterator Map< Key, Value, Compare >::lower_bound(const key_type & key)
  {
    return data_.lower_bound({key, mapped_type{}});
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::const_iterator Map< Key, Value, Compare >::lower_bound(const key_type & key) const
  {
    return data_.lower_bound({key, mapped_type{}});
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::iterator Map< Key, Value, Compare >::upper_bound(const key_type & key)
  {
    return data_.upper_bound({key, mapped_type{}});
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::const_iterator Map< Key, Value, Compare >::upper_bound(const key_type & key) const
  {
    return data_.upper_bound({key, mapped_type{}});
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::key_compare Map< Key, Value, Compare >::key_comp() const
  {
    return comp_;
  }

  template< typename Key, typename Value, typename Compare >
  typename Map< Key, Value, Compare >::value_compare Map< Key, Value, Compare >::value_comp() const
  {
    return value_compare();
  }

  template< typename Key, typename Value, typename Compare >
  bool Map< Key, Value, Compare >::isEqual(const this_t & rhs)
  {
    return data_ == rhs.data_;
  }

  template< typename Key, typename Value, typename Compare >
  class Map< Key, Value, Compare >::value_compare
  {
    friend class Map< Key, Value, Compare >;
    friend class UnbalancedBinarySearchTree< value_type, value_compare >;
   public:
    using result_type = bool;
    using first_argument_type = value_type;
    using second_argument_type = value_type;
    bool operator()(const value_type & lhs, const value_type & rhs) const
    {
      return comp(lhs.first, rhs.first);
    };
   protected:
    Compare comp;
    value_compare():
     comp()
    {}
    explicit value_compare(Compare c):
     comp(c)
    {}
  };

  template< typename Key, typename Value, typename Compare >
  bool operator==(const Map< Key, Value, Compare > & lhs, const Map< Key, Value, Compare > & rhs)
  {
    return lhs.isEqual(rhs);
  }

  template< typename Key, typename Value, typename Compare >
  bool operator!=(const Map< Key, Value, Compare > & lhs, const Map< Key, Value, Compare > & rhs)
  {
    return !(lhs == rhs);
  }
}

#endif
