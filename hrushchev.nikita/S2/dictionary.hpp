#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <utility>
#include <stdexcept>
#include <list.hpp>
#include <forwardlist.hpp>
#include <forwardlistiterator.hpp>
#include <forwardlistconstiterator.hpp>

namespace hrushchev
{
  template< typename Key, typename Value, typename Compare = std::less< > >
  class Dictionary
  {
  public:
    using iterator = ForwardListIterator< std::pair< Key, Value > >;
    using const_iterator = ForwardListConstIterator< std::pair< Key, Value > >;
    Dictionary();
    ~Dictionary() = default;
    Dictionary(const Dictionary& other);
    Dictionary(Dictionary&& other);
    Dictionary< Key, Value, Compare >& operator=(const Dictionary& other);
    Dictionary< Key, Value, Compare >& operator=(Dictionary&& other);
    iterator begin() noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator cend() const noexcept;
    iterator insert(const std::pair< Key, Value >& value);
    iterator insert(std::pair< Key, Value >&& value);
    Value& operator[](const Key& key);
    iterator find(const Key& key);
    const_iterator find(const Key& key) const;
    Value& at(const Key& key);
    iterator erase(iterator pos);
    iterator erase(const_iterator pos);
    iterator erase(iterator first, iterator last);
    iterator erase(const_iterator first, const_iterator last);
    void swap(Dictionary& other);
    size_t size() const;
    bool empty() const;
    void push(Key k, Value v);
    Value get(Key k);
  private:
    ForwardList< std::pair< Key, Value > > data_;
    Compare compare_;
    size_t size_;
  };

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary():
    data_(),
    compare_(),
    size_()
  {
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(const Dictionary& other):
    data_(other.data_),
    compare_(other.compare_),
    size_(other.size_)
  {
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary(Dictionary&& other):
    data_(std::move(other.data_)),
    compare_(other.compare_),
    size_(other.size_)
  {
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >& Dictionary< Key, Value, Compare >::operator=(const Dictionary& other)
  {
    if (this == std::addressof(other))
    {
      return *this;
    }
    data_ = other.data_;
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >& Dictionary< Key, Value, Compare >::operator=(Dictionary&& other)
  {
    if (this == std::addressof(other))
    {
      return *this;
    }
    data_ = std::move(other.data_);
    return *this;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::begin() noexcept
  {
    return data_.begin();
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
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cend() const noexcept
  {
    return data_.cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::insert(const std::pair< Key, Value >& value)
  {
    if (begin() == end())
    {
      data_.push_front(value);
      size_++;
      return begin();
    }

    auto prev = begin();
    auto cur = ++begin();

    if (prev->first == value.first)
    {
      prev->second = value.second;
      return prev;
    }

    if (!compare_(prev->first, value.first))
    {
      data_.push_front(value);
      size_++;
      return begin();
    }

    while (cur != end() && compare_(cur->first, value.first))
    {
      prev++;
      cur++;
    }

    if (cur == end() || (cur->first != value.first))
    {
      data_.insert_after(prev, value);
      size_++;
      return cur;
    }
    else
    {
      cur->second = value.second;
      return prev;
    }
    return prev;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::insert(std::pair< Key, Value >&& value)
  {
    return insert(value);
  }

  template< typename Key, typename Value, typename Compare >
  Value& Dictionary< Key, Value, Compare >::operator[](const Key& key)
  {
    for (auto cur = begin(); cur != end(); cur++)
    {
      if (cur->first == key)
      {
        return cur->second;
      }
    }
    auto res = insert(std::pair< Key, Value >(key, Value()));
    return res->second;
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::find(const Key& key)
  {
    for (auto cur = begin(); cur != end(); cur++)
    {
      if (cur->first == key)
      {
        return cur;
      }
    }
    return end();
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::find(const Key& key) const
  {
    return const_iterator(find(key));
  }

  template< typename Key, typename Value, typename Compare >
  Value& Dictionary< Key, Value, Compare >::at(const Key& key)
  {
    for (auto cur = begin(); cur != end(); cur++)
    {
      if (cur->first == key)
      {
        return cur->second;
      }
    }
    throw std::out_of_range("No such key in dictionary");
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::erase(iterator pos)
  {
    if (pos == begin())
    {
      data_.pop_front();
      size_--;
      return begin();
    }
    else if (pos == end())
    {
      return end();
    }
    auto prev = begin();
    auto cur = ++begin();
    while (cur != pos)
    {
      prev++;
      cur++;
    }
    size_--;
    return data_.erase_after(prev);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::erase(const_iterator pos)
  {
    return erase(iterator(pos));
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::erase(iterator first, iterator last)
  {
    data_.erase_after(first, last);
    return erase(first);
  }

  template< typename Key, typename Value, typename Compare >
  typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::erase(const_iterator first, const_iterator last)
  {
    return erase(iterator(first), iterator(last));
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::swap(Dictionary& other)
  {
    data_.swap(other.data_);
    std::swap(compare_, other.compare_);
    std::swap(size_, other.size_);
  }

  template< typename Key, typename Value, typename Compare >
  size_t Dictionary< Key, Value, Compare >::size() const
  {
    return size_;
  }

  template< typename Key, typename Value, typename Compare >
  bool Dictionary< Key, Value, Compare >::empty() const
  {
    return data_.empty();
  }

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::push(Key k, Value v)
  {
    insert(std::pair< Key, Value >(k, v));
  }

  template< typename Key, typename Value, typename Compare >
  Value Dictionary< Key, Value, Compare >::get(Key k)
  {
    return (*this)[k];
  }
}

#endif
