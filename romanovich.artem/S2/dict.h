#ifndef DICT_H
#define DICT_H
#include "common/listnode.h"
#include "forwardlist.h"
template< typename Key, typename Value, typename Compare = std::less< Key >>
class Dictionary
{
public:
  using keyT = Key;
  using valueT = std::pair< const Key, Value >;
  using iterator = typename ForwardList< valueT >::iterator;
  using const_iterator = typename ForwardList< valueT >::const_iterator;
  Dictionary();
  Dictionary(const Dictionary< Key, Value, Compare > &rhs);
  Dictionary(Dictionary< Key, Value, Compare > &&rhs) noexcept;
  ~Dictionary() = default;
  Dictionary< Key, Value, Compare > &operator=(const Dictionary< Key, Value, Compare > &rhs);
  Dictionary< Key, Value, Compare > &operator=(Dictionary< Key, Value, Compare > &&rhs) noexcept;
  Dictionary< Key, Value, Compare > &operator=(std::initializer_list< valueT > initializerList);
  Value &operator[](const keyT &key);
  Value &operator[](keyT &&key);
  Value &at(const keyT &key);
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
  size_t size() const noexcept;
  void clear() noexcept;
  //
  std::pair< iterator, bool > insert(const valueT &value);
  template< typename P >
  std::pair< iterator, bool > insert(P &&value);
  iterator insert(const_iterator pos, const valueT &value);
  template< typename P >
  iterator insert(const_iterator pos, P &&value);
  template< typename InputIt >
  void insert(InputIt first, InputIt last);
  void insert(std::initializer_list< valueT > initializerList);
//
  template< typename... Args >
  std::pair< iterator, bool > emplace(Args &&... args);
  template< typename... Args >
  iterator emplace(const_iterator pos, Args &&... args);
  iterator erase_after(const_iterator pos);
  iterator erase_after(const_iterator first, const_iterator last);
  size_t erase(const keyT &key);
  void swap(Dictionary< Key, Value, Compare > &other);
  size_t count(const keyT &key) const;
  iterator find(const keyT &key);
  const_iterator find(const keyT &key) const;
  std::pair< iterator, iterator > equal_range(const keyT &key);
  std::pair< const_iterator, const_iterator > equal_range(const keyT &key) const;
  iterator lower_bound(const keyT &key);
  const_iterator lower_bound(const keyT &key) const;
  iterator upper_bound(const keyT &key);
  const_iterator upper_bound(const keyT &key) const;
  Compare key_comp() const;
private:
  ForwardList< valueT > data_;
  Compare comp_;
  size_t size_;
  Value &insertValue(keyT &&key);
  bool areEqualKeys(keyT lhs, keyT rhs);
};
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
    details::ListNode< valueT > *current = eraseStart.node_->next;
    details::ListNode< valueT > *end = eraseEnd.node_->next;
    eraseStart.node_->next = end;
    while (current != end)
    {
      details::ListNode< valueT > *next = current->next;
      delete current;
      current = next;
    }
  }
  return iterator(it.node_);
}
template< typename Key, typename Value, typename Compare >
void Dictionary< Key, Value, Compare >::swap(Dictionary< Key, Value, Compare > &other)
{
  data_.swap(other.data_);
  std::swap(comp_, other.comp_);
}
template< typename Key, typename Value, typename Compare >
size_t Dictionary< Key, Value, Compare >::count(const keyT &key) const
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
typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::find(const keyT &key)
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
Dictionary< Key, Value, Compare >::equal_range(const keyT &key)
{
  iterator lower = lower_bound(key);
  iterator upper = upper_bound(key);
  return std::pair< iterator, iterator >(lower, upper);
}
template< typename Key, typename Value, typename Compare >
std::pair< typename Dictionary< Key, Value, Compare >::const_iterator, typename Dictionary< Key, Value, Compare >::const_iterator >
Dictionary< Key, Value, Compare >::equal_range(const keyT &key) const
{
  const_iterator lower = lower_bound(key);
  const_iterator upper = upper_bound(key);
  return std::pair< const_iterator, const_iterator >(lower, upper);
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::const_iterator
Dictionary< Key, Value, Compare >::find(const keyT &key) const
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
typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::lower_bound(const keyT &key)
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
Dictionary< Key, Value, Compare >::lower_bound(const keyT &key) const
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
  valueT value(std::forward< Args >(args)...);
  return insert(std::move(value));
}
template< typename Key, typename Value, typename Compare >
void Dictionary< Key, Value, Compare >::insert(std::initializer_list< valueT > initializerList)
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
Dictionary< Key, Value, Compare >::insert(Dictionary::const_iterator pos, const Dictionary::valueT &value)
{
  return data_.insert_after(pos, value);
}
template< typename Key, typename Value, typename Compare >
template< typename P >
std::pair< typename Dictionary< Key, Value, Compare >::iterator, bool >
Dictionary< Key, Value, Compare >::insert(P &&value)
{
  valueT tmpValue(std::forward< P >(value));
  iterator it = lower_bound(tmpValue.first);
  if (it != end() && !comp_(tmpValue.first, it->first) && !comp_(it->first, tmpValue.first))
  {
    return std::make_pair(it, false);
  }
  iterator insertedIt = data_.insert_after(it, std::move(tmpValue));
  return std::make_pair(insertedIt, true);
}
template< typename Key, typename Value, typename Compare >
bool Dictionary< Key, Value, Compare >::areEqualKeys(keyT lhs, keyT rhs)
{
  return (comp_(lhs, rhs) || comp_(rhs, lhs));
}
template< typename Key, typename Value, typename Compare >
size_t Dictionary< Key, Value, Compare >::erase(const keyT &key)
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
typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::upper_bound(const keyT &key)
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
Dictionary< Key, Value, Compare >::upper_bound(const keyT &key) const
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
Dictionary< Key, Value, Compare >::insert(const Dictionary::valueT &value)
{
  valueT newValue = value;
  auto it = find(newValue.first);
  if (it != end())
  {
    return {it, false};
  }
  data_.push_back(std::move(newValue));
  ++size_;
  it = find(newValue.first);
  return {it, true};
}
template< typename Key, typename Value, typename Compare >
void Dictionary< Key, Value, Compare >::clear() noexcept
{
  data_.clear();
  size_ = 0;
}
template< typename Key, typename Value, typename Compare >
size_t Dictionary< Key, Value, Compare >::size() const noexcept
{
  return size_;
}
template< typename Key, typename Value, typename Compare >
bool Dictionary< Key, Value, Compare >::empty() const noexcept
{
  return size_ == 0;
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::clast() const noexcept
{
  return last();
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::last() const noexcept
{
  return data_.clast(); //TODO
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::last() noexcept
{
  return data_.last(); //TODO
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::cend() const noexcept
{
  return end();
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::end() const noexcept
{
  return data_.cend();
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
typename Dictionary< Key, Value, Compare >::const_iterator Dictionary< Key, Value, Compare >::begin() const noexcept
{
  return data_.cbegin();
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
typename Dictionary< Key, Value, Compare >::const_iterator
Dictionary< Key, Value, Compare >::before_begin() const noexcept
{
  return data_.cbefore_begin();
}
template< typename Key, typename Value, typename Compare >
typename Dictionary< Key, Value, Compare >::iterator Dictionary< Key, Value, Compare >::before_begin() noexcept
{
  return data_.before_begin();
}
template< typename Key, typename Value, typename Compare >
Value &Dictionary< Key, Value, Compare >::at(const keyT &key)
{
  iterator it = find(key);
  if (it == end())
  {
    throw std::out_of_range("Key in dict not found.");
  }
  return it->second;
}
template< typename Key, typename Value, typename Compare >
Value &Dictionary< Key, Value, Compare >::insertValue(keyT &&key)
{
  try
  {
    return at(key);
  }
  catch (const std::out_of_range &)
  {
    valueT newValue(std::forward< keyT >(key), Value{});
    std::pair< iterator, bool > insertionResult = insert(std::move(newValue));
    return insertionResult.first->second;
  }
}
template< typename Key, typename Value, typename Compare >
Value &Dictionary< Key, Value, Compare >::operator[](const keyT &key)
{
  return insertValue(key);
}
template< typename Key, typename Value, typename Compare >
Value &Dictionary< Key, Value, Compare >::operator[](keyT &&key)
{
  return insertValue(std::move(key));
}
template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare > &Dictionary< Key, Value, Compare >::operator=(
  Dictionary< Key, Value, Compare > &&rhs) noexcept
{
  if (this != &rhs)
  {
    data_ = std::move(rhs.data_);
    comp_ = std::move(rhs.comp_);
    size_ = rhs.size_;
    rhs.size_ = 0;
  }
  return *this;
}
template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare > &Dictionary< Key, Value, Compare >::operator=(
  std::initializer_list< valueT > initializerList)
{
  data_.clear();
  insert(initializerList);
  return *this;
}
template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare >::Dictionary(Dictionary< Key, Value, Compare > &&rhs) noexcept:
  data_(std::move(rhs.data_)),
  comp_(std::move(rhs.comp_)),
  size_(rhs.size_)
{
  rhs.size_ = 0;
}
template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare > &Dictionary< Key, Value, Compare >::operator=(
  const Dictionary< Key, Value, Compare > &rhs)
{
  details::copy(data_);
}
template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare >::Dictionary():
  data_(),
  comp_(),
  size_(0)
{
}
template< typename Key, typename Value, typename Compare >
Dictionary< Key, Value, Compare >::Dictionary(const Dictionary< Key, Value, Compare > &other):
  size_(other.size_),
  comp_(other.comp_)
{
  data_.insert(other.begin(), other.end());
}
#endif
