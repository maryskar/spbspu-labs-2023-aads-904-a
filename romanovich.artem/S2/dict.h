#ifndef DICT_H
#define DICT_H
#include "common/listnode.h"
#include "forwardlist.h"
template< typename Key, typename Value, typename Compare = std::less< Key >>
class Dictionary
{
public:
  using value_type = std::pair< const Key, Value >;
  using iterator = typename ForwardList< value_type >::iterator;
  using const_iterator = typename ForwardList< value_type >::const_iterator;
  Dictionary();
  Dictionary(const Dictionary< Key, Value, Compare > &other);
  Dictionary(Dictionary< Key, Value, Compare > &&other) noexcept;
  Dictionary(std::initializer_list< value_type > other);
  ~Dictionary() = default;
  Dictionary< Key, Value, Compare > &operator=(const Dictionary< Key, Value, Compare > &other);
  Dictionary< Key, Value, Compare > &operator=(Dictionary< Key, Value, Compare > &&other) noexcept;
  Dictionary< Key, Value, Compare > &operator=(std::initializer_list< value_type > initializerList);
  Value &operator[](const Key &key);
  Value &operator[](Key &&key);
  Value &at(const Key &key);
  iterator before_begin() noexcept;
  iterator before_begin() const noexcept;
  const_iterator cbefore_begin() const noexcept;
  iterator begin() noexcept;
  iterator begin() const noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  iterator end() const noexcept;
  const_iterator cend() const noexcept;
  iterator last() noexcept;
  iterator last() const noexcept;
  const_iterator clast() const noexcept;
  bool empty() const noexcept;
  void clear() noexcept;
  std::pair< iterator, bool > insert(const value_type &value);
  template< typename P >
  std::pair< iterator, bool > insert(P &&value);
  iterator insert(const_iterator pos, const value_type &value);
  template< typename P >
  iterator insert(const_iterator pos, P &&value);
  template< typename InputIt >
  void insert(InputIt first, InputIt last);
  void insert(std::initializer_list< value_type > initializerList);
  template< typename... Args >
  std::pair< iterator, bool > emplace(Args &&... args);
  template< typename... Args >
  iterator emplace(const_iterator pos, Args &&... args);
  iterator erase_after(const_iterator pos);
  iterator erase_after(const_iterator first, const_iterator last);
  size_t erase(const Key &key);
  void swap(Dictionary< Key, Value, Compare > &other);
  size_t count(const Key &key) const;
  iterator find(const Key &key);
  const_iterator find(const Key &key) const;
  std::pair< iterator, iterator > equal_range(const Key &key);
  std::pair< const_iterator, const_iterator > equal_range(const Key &key) const;
  iterator lower_bound(const Key &key);
  const_iterator lower_bound(const Key &key) const;
  iterator upper_bound(const Key &key);
  const_iterator upper_bound(const Key &key) const;
  Compare key_comp() const;
  ForwardList< value_type > data_;
private:
  Compare comp_;
  Value &insertValue(Key &&key);
  bool areEqualKeys(Key lhs, Key other);
};
template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare > &Dictionary< Key, Value, Compare >::operator=(
  Dictionary< Key, Value, Compare > &&other) noexcept
{
  if (this != &other)
  {
    data_ = std::move(other.data_);
    comp_ = std::move(other.comp_);
  }
  return *this;
}
template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare >::Dictionary(std::initializer_list< value_type > other):
  data_(other),
  comp_()
{
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::iterator
Dictionary< Key, Value, Compare >::erase_after(Dictionary::const_iterator first, Dictionary::const_iterator last)
{
  if (first == last || first == data_.cend())
  {
    return iterator(data_.end());
  }
  iterator it = data_.begin();
  while (it != data_.end() && it != first)
  {
    ++it;
  }
  if (it == data_.end())
  {
    return iterator(data_.end());
  }
  iterator eraseStart = ++it;
  while (it != data_.end() && it != last)
  {
    ++it;
  }
  if (eraseStart != it)
  {
    iterator eraseEnd = it;
    ++eraseEnd;
    details::ListNode< value_type > *current = eraseStart.head_->next;
    details::ListNode< value_type > *end = eraseEnd.head_->next;
    eraseStart.head_->next = end;
    while (current != end)
    {
      details::ListNode< value_type > *next = current->next;
      delete current;
      current = next;
    }
  }
  return iterator(it.head_);
}
template< typename Key, typename Value, typename Compare >
void Dictionary< Key, Value, Compare >::swap(Dictionary< Key, Value, Compare > &other)
{
  data_.swap(other.data_);
  std::swap(comp_, other.comp_);
}
template< typename Key, typename Value, typename Compare >
size_t Dictionary< Key, Value, Compare >::count(const Key &key) const
{
  size_t count = 0;
  const_iterator it = data_.cbegin();
  const_iterator endIt = data_.cend();
  while (it != endIt)
  {
    if (!comp_(key, it->first) && !comp_(it->first, key))
    {
      ++count;
    }
    ++it;
  }
  return count;
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::iterator
Dictionary< Key, Value, Compare >::erase_after(Dictionary::const_iterator pos)
{
  if (pos == cend() || ++pos == cend())
  {
    return end();
  }
  const_iterator eraseIt = pos;
  const_iterator nextIt = ++pos;
  data_.erase_after(eraseIt.getIterator());
  return iterator(nextIt.getIterator());
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::find(const Key &key)
{
  iterator it = data_.begin();
  while (it != data_.end())
  {
    if (!comp_(it->first, key) && !comp_(key, it->first))
    {
      return it;
    }
    ++it;
  }
  return end();
}
template< typename Key, typename Value, typename Compare >
std::pair< typename Dictionary< Key, Value, Compare >::iterator, typename Dictionary< Key, Value, Compare >::iterator >
Dictionary< Key, Value, Compare >::equal_range(const Key &key)
{
  iterator lower = lower_bound(key);
  iterator upper = upper_bound(key);
  return std::pair< iterator, iterator >(lower, upper);
}
template< typename Key, typename Value, typename Compare >
std::pair< typename Dictionary< Key, Value, Compare >::const_iterator, typename Dictionary< Key, Value, Compare >::const_iterator >
Dictionary< Key, Value, Compare >::equal_range(const Key &key) const
{
  const_iterator lower = lower_bound(key);
  const_iterator upper = upper_bound(key);
  return std::pair< const_iterator, const_iterator >(lower, upper);
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::const_iterator
Dictionary< Key, Value, Compare >::find(const Key &key) const
{
  for (const_iterator it = cbegin(); it != cend(); ++it)
  {
    if (!comp_(it->first, key) && !comp_(key, it->first))
    {
      return it;
    }
  }
  return cend();
}
template< typename Key, typename Value, typename Compare >
template< typename... Args >
typename Dictionary< Key, Value, Compare >::iterator
Dictionary< Key, Value, Compare >::emplace(Dictionary::const_iterator pos, Args &&... args)
{
  iterator it = data_.insert_after(pos.getIterator(), std::forward< Args >(args)...);
  return it;
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::lower_bound(const Key &key)
{
  iterator it = data_.begin();
  while (it != data_.end() && comp_(it->first, key))
  {
    ++it;
  }
  return it;
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::const_iterator
Dictionary< Key, Value, Compare >::lower_bound(const Key &key) const
{
  const_iterator it = data_.cbegin();
  while (it != data_.cend() && comp_(it->first, key))
  {
    ++it;
  }
  return it;
}
template< typename Key, typename Value, typename Compare >
template< typename... Args >
std::pair< typename Dictionary< Key, Value, Compare >::iterator, bool >
Dictionary< Key, Value, Compare >::emplace(Args &&... args)
{
  return insert(value_type(std::forward< Args >(args)...));
}
template< typename Key, typename Value, typename Compare >
void Dictionary< Key, Value, Compare >::insert(std::initializer_list< value_type > initializerList)
{
  data_.insert_after(data_.before_begin(), initializerList.begin(), initializerList.end());
}
template< typename Key, typename Value, typename Compare >
template< typename InputIt >
void Dictionary< Key, Value, Compare >::insert(InputIt first, InputIt last)
{
  data_.insert_after(data_.before_begin(), first, last);
}
template< typename Key, typename Value, typename Compare >
template< typename P >
typename Dictionary< Key, Value, Compare >::iterator
Dictionary< Key, Value, Compare >::insert(Dictionary::const_iterator pos, P &&value)
{
  return data_.insert_after(pos, std::forward< P >(value));
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::iterator
Dictionary< Key, Value, Compare >::insert(Dictionary::const_iterator pos, const Dictionary::value_type &value)
{
  return data_.insert_after(pos, value);
}
template< typename Key, typename Value, typename Compare >
template< typename P >
std::pair< typename Dictionary< Key, Value, Compare >::iterator, bool >
Dictionary< Key, Value, Compare >::insert(P &&value)
{
  /*auto it = data_.begin();
  auto prev = data_.before_begin();
  for (; it != data_.end(); it++)
  {
    if (comp_(value.first, (*it).first))
    {
      break;
    }
    prev = it;
  }
  if (prev != data_.before_begin() && areEqualKeys(prev->first, value.first))
  {
    (*prev).second = value.second;
  }
  else
  {
    data_.insert_after(prev, value);
  }
  return std::make_pair(iterator(prev), false);*/
  value_type tmpValue(std::forward< P >(value));
  iterator it = lower_bound(tmpValue.first);
  if (it != end() && areEqualKeys(tmpValue.first, it->first))
  {
    /////
    return std::make_pair(it, false);
  }
  iterator insertedIt = data_.emplace_front(std::move(tmpValue));
  return std::make_pair(insertedIt, true);
}
template< typename Key, typename Value, typename Compare >
bool Dictionary< Key, Value, Compare >::areEqualKeys(Key lhs, Key other)
{
  return !comp_(lhs, other) && !comp_(other, lhs);
}
template< typename Key, typename Value, typename Compare >
size_t Dictionary< Key, Value, Compare >::erase(const Key &key)
{
  size_t count = 0;
  iterator it = data_.begin();
  while (it != data_.end())
  {
    if (!areEqualKeys(it->first, key))
    {
      ++it;
    }
    else
    {
      it = data_.erase_after(it);
      ++count;
    }
  }
  return count;
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::upper_bound(const Key &key)
{
  iterator it = data_.begin();
  while (it != data_.end() && !comp_(key, it->first))
  {
    ++it;
  }
  return it;
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::const_iterator
Dictionary< Key, Value, Compare >::upper_bound(const Key &key) const
{
  return const_cast<Dictionary *>(this)->upper_bound(key);
}
template< typename Key, typename Value, typename Compare >
Compare Dictionary< Key, Value, Compare >::key_comp() const
{
  return comp_;
}
template< typename Key, typename Value, typename Compare >
std::pair< typename ForwardList< std::pair< const Key, Value > >::iterator, bool >
Dictionary< Key, Value, Compare >::insert(const Dictionary::value_type &value)
{
  auto it = find(value.first);
  if (it != end())
  {
    return {it, false};
  }
  data_.push_back(std::move(value));
  it = find(value.first);
  return {it, true};
}
template< typename Key, typename Value, typename Compare >
void Dictionary< Key, Value, Compare >::clear() noexcept
{
  data_.clear();
}
template< typename Key, typename Value, typename Compare >
bool Dictionary< Key, Value, Compare >::empty() const noexcept
{
  return data_.empty();
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::clast() const noexcept
{
  return last();
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::last() const noexcept
{
  return data_.last();
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::last() noexcept
{
  return data_.last();
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cend() const noexcept
{
  return end();
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::end() const noexcept
{
  return data_.end();
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::end() noexcept
{
  return data_.end();
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cbegin() const noexcept
{
  return data_.cbegin();
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::begin() const noexcept
{
  return data_.begin();
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::begin() noexcept
{
  return data_.begin();
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::const_iterator
Dictionary< Key, Value, Compare >::cbefore_begin() const noexcept
{
  return data_.cbefore_begin();
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::iterator
Dictionary< Key, Value, Compare >::before_begin() const noexcept
{
  return data_.before_begin();
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::before_begin() noexcept
{
  return data_.before_begin();
}
template< typename Key, typename Value, typename Compare >
Value &Dictionary< Key, Value, Compare >::at(const Key &key)
{
  iterator it = find(key);
  if (it == end())
  {
    throw std::out_of_range("Key in dict not found.");
  }
  return it->second;
}
template< typename Key, typename Value, typename Compare >
Value &Dictionary< Key, Value, Compare >::insertValue(Key &&key)
{
  try
  {
    return at(key);
  }
  catch (const std::out_of_range &)
  {
    value_type newValue(std::forward< Key >(key), Value{});
    std::pair< iterator, bool > insertionResult = insert(std::move(newValue));
    return insertionResult.first->second;
  }
}
template< typename Key, typename Value, typename Compare >
Value &Dictionary< Key, Value, Compare >::operator[](const Key &key)
{
  return insertValue(key);
}
template< typename Key, typename Value, typename Compare >
Value &Dictionary< Key, Value, Compare >::operator[](Key &&key)
{
  return insertValue(std::move(key));
}
template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare > &Dictionary< Key, Value, Compare >::operator=(
  std::initializer_list< value_type > initializerList)
{
  data_.clear();
  insert(initializerList);
  return *this;
}
template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare >::Dictionary(Dictionary< Key, Value, Compare > &&other) noexcept:
  data_(std::move(other.data_)),
  comp_(std::move(other.comp_))
{
}
template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare > &Dictionary< Key, Value, Compare >::operator=(
  const Dictionary< Key, Value, Compare > &other)
{
  if (this != std::addressof(other))
  {
    data_ = other.data_;
  }
  return *this;
}
template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare >::Dictionary():
  data_(),
  comp_()
{
}
template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare >::Dictionary(const Dictionary< Key, Value, Compare > &other):
  data_(other.data_),
  comp_(other.comp_)
{
}
#endif
