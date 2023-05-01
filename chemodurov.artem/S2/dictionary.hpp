#ifndef S2_DICTIONARY_HPP
#define S2_DICTIONARY_HPP
#include <cmath>
#include "forward-list.hpp"

namespace chemodurov
{
  template< typename Key, typename Value, typename Compare >
  class Dictionary
  {
   public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair< const Key, Value >;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using key_compare = Compare;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = typename ForwardList< value_type >::iterator;
    using const_iterator = typename ForwardList< value_type >::const_iterator;
    using this_t = Dictionary< Key, Value, Compare >;
    class value_compare;
    Dictionary();
    Dictionary(const this_t & other);
    Dictionary(this_t && other);
    explicit Dictionary(const Compare & comp);
    template< typename InputIt >
    Dictionary(InputIt first, InputIt last, const Compare & comp = Compare());
    Dictionary(std::initializer_list< value_type > init, const Compare & comp = Compare());
    ~Dictionary() = default;
    this_t & operator=(const this_t & other);
    this_t & operator=(this_t && other);
    this_t & operator=(std::initializer_list< value_type > init);
    Value & operator[](const key_type & key);
    Value & operator[](key_type && key);
    Value & at(const key_type & key);
    const Value & at(const key_type & key) const;
    iterator before_begin() noexcept;
    const_iterator before_begin() const noexcept;
    const_iterator cbefore_begin() const noexcept;
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    bool empty() const noexcept;
    size_type size() const noexcept;
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
    iterator emplace(const_iterator pos, Args && ... args);
    iterator erase_after(const_iterator pos);
    iterator erase_after(const_iterator first, const_iterator last);
    size_type erase(const key_type & key);
    void swap(this_t & other);
    size_type count(const key_type & key) const;
    template< typename K >
    size_type count(const K & k) const;
    iterator find(const key_type & key);
    const_iterator find(const key_type & key) const;
    template< typename K >
    iterator find(const K & x);
    template< typename K >
    const_iterator find(const K & x) const;
    std::pair< iterator, iterator > equal_range(const key_type & key);
    std::pair< const_iterator, const_iterator > equal_range(const key_type & key) const;
    template< typename K >
    std::pair< iterator, iterator > equal_range(const K & x);
    template< typename K >
    std::pair< const_iterator, const_iterator > equal_range(const K & x) const;
    iterator lower_bound(const key_type & key);
    const_iterator lower_bound(const key_type & key) const;
    template< typename K >
    iterator lower_bound(const K & x);
    template< typename K >
    const_iterator lower_bound(const K & x) const;
    iterator upper_bound(const key_type & key);
    const_iterator upper_bound(const key_type & key) const;
    template< typename K >
    iterator upper_bound(const K & x);
    template< typename K >
    const_iterator upper_bound(const K & x) const;
    key_compare key_comp() const;
    value_compare value_comp() const;
   private:
    ForwardList< value_type > data_;
    Compare comp_;
    size_type size_;
  };

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::key_compare Dictionary< Key, Value, Compare >::key_comp() const
  {
    return comp_;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::value_compare Dictionary< Key, Value, Compare >::value_comp() const
  {
    return value_compare(comp_);
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary():
   data_(),
   comp_(),
   size_(0)
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(const this_t & other):
   data_(other.data_),
   comp_(other.comp_),
   size_(other.size_)
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(this_t && other):
   data_(std::move(other.data_)),
   comp_(std::move(other.comp_)),
   size_(other.size_)
  {
    other.size_ = 0;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(const Compare & comp):
   data_(),
   comp_(comp),
   size_(0)
  {}

  template< typename Key, typename Value, typename Compare >
  template< typename InputIt >
  Dictionary< Key, Value, Compare >::Dictionary(InputIt first, InputIt last, const Compare & comp):
   data_(first, last),
   comp_(comp),
   size_(std::abs(std::distance(first, last)))
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(std::initializer_list< value_type > init, const Compare & comp):
   data_(init),
   comp_(comp),
   size_(init.size())
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > & Dictionary< Key, Value, Compare >::operator=(const this_t & other)
  {
    if (this == std::addressof(other))
    {
      return *this;
    }
    Compare temp = other.comp_;
    data_ = other.data_;
    comp_ = std::move(temp);
    size_ = other.size_;
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > & Dictionary< Key, Value, Compare >::operator=(this_t && other)
  {
    if (this == std::addressof(other))
    {
      return *this;
    }
    data_ = std::move(other.data_);
    comp_ = std::move(other.comp_);
    size_ = other.size_;
    other.size_ = 0;
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > & Dictionary< Key, Value, Compare >::operator=(std::initializer_list< value_type > init)
  {
    clear();
    data_ = init;
    comp_ = Compare();
    size_ = init.size();
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::begin() noexcept
  {
    return data_.begin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cbegin() const noexcept
  {
    return data_.cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::end() noexcept
  {
    return data_.end();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::end() const noexcept
  {
    return cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cend() const noexcept
  {
    return data_.cend();
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::empty() const noexcept
  {
    return cbegin() == cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::size_type Dictionary< Key, Value, Compare >::size() const noexcept
  {
    return size_;
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::clear() noexcept
  {
    data_.clear();
    size_ = 0;
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::swap(this_t & other)
  {
    data_.swap(other.data_);
    std::swap(comp_, other.comp_);
    std::swap(size_, other.size_);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::lower_bound(const key_type & key) const
  {
    const_iterator end_ = cend();
    const_iterator it = cbegin();
    const_iterator res = cbefore_begin();
    while (it != end_ && key_comp()(it->first, key))
    {
      ++it;
      ++res;
    }
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::lower_bound(const key_type & key)
  {
    iterator end_ = end();
    iterator it = begin();
    iterator res = before_begin();
    while (it != end_ && key_comp()(it->first, key))
    {
      ++it;
      ++res;
    }
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  template< typename K >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::lower_bound(const K & x)
  {
    iterator end_ = end();
    iterator it = begin();
    iterator res = before_begin();
    while (it != end_ && key_comp()(it->first, x))
    {
      ++it;
      ++res;
    }
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  template< typename K >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::lower_bound(const K & x) const
  {
    const_iterator end_ = cend();
    const_iterator it = cbegin();
    const_iterator res = cbefore_begin();
    while (it != end_ && key_comp()(it->first, x))
    {
      ++it;
      ++res;
    }
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::upper_bound(const key_type & key) const
  {
    const_iterator end_ = cend();
    const_iterator it = cbegin();
    const_iterator res = cbefore_begin();
    while (it != end_ && !(key_comp()(key, it->first)))
    {
      ++it;
      ++res;
    }
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::upper_bound(const key_type & key)
  {
    iterator end_ = end();
    iterator it = begin();
    iterator res = before_begin();
    while (it != end_ && !(key_comp()(key, it->first)))
    {
      ++it;
      ++res;
    }
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  template< typename K >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::upper_bound(const K & x)
  {
    iterator end_ = end();
    iterator it = begin();
    iterator res = before_begin();
    while (it != end_ && !(key_comp()(x, it->first)))
    {
      ++it;
      ++res;
    }
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  template< typename K >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::upper_bound(const K & x) const
  {
    const_iterator end_ = cend();
    const_iterator it = cbegin();
    const_iterator res = cbefore_begin();
    while (it != end_ && !(key_comp()(x, it->first)))
    {
      ++it;
      ++res;
    }
    return res;
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< typename Dictionary< Key, Value, Compare >::iterator,
      typename Dictionary< Key, Value, Compare >::iterator >
          Dictionary< Key, Value, Compare >::equal_range(const key_type & key)
  {
    return std::pair< iterator, iterator >(lower_bound(key), ++(upper_bound(key)));
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< typename Dictionary< Key, Value, Compare >::const_iterator,
      typename Dictionary< Key, Value, Compare >::const_iterator >
          Dictionary< Key, Value, Compare >::equal_range(const key_type & key) const
  {
    return std::pair< iterator, iterator >(lower_bound(key), ++(upper_bound(key)));
  }

  template< typename Key, typename Value, typename Compare >
  template< typename K >
  std::pair< typename Dictionary< Key, Value, Compare >::iterator,
      typename Dictionary< Key, Value, Compare >::iterator >
          Dictionary< Key, Value, Compare >::equal_range(const K & x)
  {
    return std::pair< iterator, iterator >(lower_bound(x), ++(upper_bound(x)));
  }

  template< typename Key, typename Value, typename Compare >
  template< typename K >
  std::pair< typename Dictionary< Key, Value, Compare >::const_iterator,
      typename Dictionary< Key, Value, Compare >::const_iterator >
          Dictionary< Key, Value, Compare >::equal_range(const K & x) const
  {
    return std::pair< iterator, iterator >(lower_bound(x), ++(upper_bound(x)));
  }

  template< typename Key, typename Value, typename Compare >
  template< typename K >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::find(const K & x)
  {
    iterator it = lower_bound(x);
    iterator moved_it = it;
    ++moved_it;
    return moved_it->first == x ? it : cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::find(const key_type & key) const
  {
    const_iterator cit = lower_bound(key);
    const_iterator moved_cit = cit;
    ++moved_cit;
    return moved_cit->first == key ? cit : cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::find(const key_type & key)
  {
    iterator it = lower_bound(key);
    iterator moved_it = it;
    ++moved_it;
    return moved_it->first == key ? it : cend();
  }

  template< typename Key, typename Value, typename Compare >
  template< typename K >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::find(const K & x) const
  {
    const_iterator cit = lower_bound(x);
    const_iterator moved_cit = cit;
    ++moved_cit;
    return moved_cit->first == x ? cit : cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::size_type Dictionary< Key, Value, Compare >::count(const key_type & key) const
  {
    return ++(find(key)) == end() ? 0ull : 1ull;
  }

  template< typename Key, typename Value, typename Compare >
  template< typename K >
  typename Dictionary< Key, Value, Compare >::size_type Dictionary< Key, Value, Compare >::count(const K & x) const
  {
    return ++(find(x)) == end() ? 0ull : 1ull;
  }

  template< typename Key, typename Value, typename Compare >
  const Value & Dictionary< Key, Value, Compare >::at(const key_type & key) const
  {
    const_iterator it = find(key);
    if (++it == cend())
    {
      throw std::out_of_range("There is no such key");
    }
    return it->second;
  }

  template< typename Key, typename Value, typename Compare >
  Value & Dictionary< Key, Value, Compare >::at(const key_type & key)
  {
    return const_cast< Value & >((static_cast< const this_t & >(*this)).at(key));
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::before_begin() noexcept
  {
    return data_.before_begin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::before_begin() const noexcept
  {
    return cbefore_begin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cbefore_begin() const noexcept
  {
    return data_.cbefore_begin();
  }

  template< typename Key, typename Value, typename Compare >
  std::pair< typename Dictionary< Key, Value, Compare >::iterator,
      bool > Dictionary< Key, Value, Compare >::insert(const value_type & value)
  {
    iterator it = lower_bound(value.first);
    iterator moved_it = it;
    ++moved_it;
    if (moved_it->first == value.first)
    {
      moved_it->second = value.second;
      return {moved_it, false};
    }
    data_.insert_after(it, value);
    return {moved_it, true};
  }

  template< typename Key, typename Value, typename Compare >
  template< typename P >
  std::pair< typename Dictionary< Key, Value, Compare >::iterator, bool > Dictionary< Key, Value, Compare >::insert(P && value)
  {
    return insert(value_type(std::forward< P >(value)));
  }

  //template< typename Key, typename Value, typename Compare >
  //typename Dictionary< Key, Value, Compare >::iterator
  //    Dictionary< Key, Value, Compare >::insert(const_iterator pos, const value_type & value)
  //{
  //  return ;
  //}
  template< typename Key, typename Value, typename Compare >
  class Dictionary< Key, Value, Compare >::value_compare
  {
   public:
    using result_type = bool;
    using first_argument_type = value_type;
    using second_argument_type = value_type;
    bool operator()( const value_type& lhs, const value_type& rhs ) const
    {
      return comp(lhs.first, rhs.first);
    };
   protected:
    Compare comp;
    explicit value_compare(Compare c): comp(c) {};
  };
}
#endif
