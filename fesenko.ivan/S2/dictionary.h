#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "forwardList.h"

namespace fesenko
{
  template< typename Key, typename Value, typename Compare >
  class Dictionary
  {
   public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair< const key_type, mapped_type >;
    using key_compare = Compare;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using iterator = typename ForwardList< value_type >::iterator;
    using const_iterator = typename ForwardList< value_type >::const_iterator;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;
    using this_t = Dictionary< Key, Value, Compare >;
    class value_compare;
    Dictionary();
    explicit Dictionary(const key_compare &);
    Dictionary(const this_t &);
    Dictionary(this_t &&);
    ~Dictionary() = default;
    this_t &operator=(const this_t &);
    this_t &operator=(this_t &&);
    iterator before_begin() noexcept;
    const_iterator before_begin() const noexcept;
    const_iterator cbefore_begin() const noexcept;
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    iterator last() noexcept;
    const_iterator last() const noexcept;
    const_iterator clast() const noexcept;
    bool empty() const noexcept;
    size_type size() const noexcept;
    mapped_type &operator[](const key_type &);
    mapped_type &operator[](key_type &&);
    mapped_type &at(const key_type &);
    const mapped_type &at(const key_type &) const;
    std::pair< iterator, bool > insert(const value_type &);
    template< typename P >
    std::pair< iterator, bool > insert(P &&);
    iterator insert(const_iterator, const value_type &);
    template< typename P >
    iterator insert(const_iterator, P &&);
    template< typename InputIt >
    void insert(InputIt, InputIt);
    iterator erase(const_iterator);
    size_type erase(const key_type &);
    iterator erase(const_iterator, const_iterator);
    void swap(this_t &);
    void clear() noexcept;
    key_compare key_comp() const;
    value_compare value_comp() const;
    iterator find(const key_type & key);
    const_iterator find(const key_type & key) const;
   private:
    ForwardList< value_type > list_;
    Compare comp_;
    size_type size_;
  };

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary():
    list_(),
    comp_(),
    size_(0)
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(const key_compare &comp):
    list_(),
    comp_(comp),
    size_(0)
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(const this_t &other):
    list_(other.list_),
    comp_(other.comp_),
    size_(other.size_)
  {}

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(this_t &&other):
    list_(std::move(other.list_)),
    comp_(std::move(other.comp_)),
    size_(other.size_)
  {
    other.size_ = 0;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > &Dictionary< Key, Value, Compare >::operator=(const this_t &other)
  {
    if (this != std::addressof(other)) {
      Compare temp = other.comp_;
      list_ = other.list_;
      comp_ = std::move(temp);
      size_ = other.size_;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare > &Dictionary< Key, Value, Compare >::operator=(this_t &&other)
  {
    if (this != std::addressof(other)) {
      list_ = std::move(other.list_);
      comp_ = std::move(other.comp_);
      size_ = other.size_;
      other.size_ = 0;
    }
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::begin() noexcept
  {
    return list_.begin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cbegin() const noexcept
  {
    return list_.cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::end() noexcept
  {
    return list_.end();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::end() const noexcept
  {
    return cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cend() const noexcept
  {
    return list_.cend();
  }
}
#endif
