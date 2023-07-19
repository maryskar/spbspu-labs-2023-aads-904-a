#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>


#include <utility>
#include <list.hpp>
#include "forwardlist.hpp"
#include "forwardlistiterator.hpp"
#include "forwardlistconstiterator.hpp"

template< typename Key, typename Value, typename Compare = std::less< > >
class Dictionary
{
public:
  using iterator = ForwardListIterator< std::pair< Key, Value > >;
  using const_iterator = ForwardListConstIterator< std::pair< Key, Value > >;
  Dictionary();
  ~Dictionary() = default;
  iterator begin() noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator cend() const noexcept;
  iterator insert(const std::pair< Key, Value >& value);
  iterator insert(std::pair< Key, Value >&& value);
  Value& operator[](const Key& key);
  iterator find(const Key& key);
  const_iterator find(const Key& key) const;
  void push(Key k, Value v);
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
}

template< typename Key, typename Value, typename Compare >
void Dictionary< Key, Value, Compare >::push(Key k, Value v)
{
  insert(std::pair< Key, Value >(k, v));
}

#endif
