#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include "common/listnode.h"
#include "forwardlistiter.h"
#include "constforwardlistiter.h"
template< typename T >
class ForwardList
{
public:
  using const_iterator = ConstForwardListIterator< T >;
  using iterator = ForwardListIterator< T >;
  ForwardList();
  ForwardList(const ForwardList &rhs);
  ForwardList(ForwardList &&rhs) noexcept;
  ForwardList(std::initializer_list< T > initializerList);
  ~ForwardList();
  ForwardList &operator=(const ForwardList &rhs);
  ForwardList &operator=(ForwardList &&rhs) noexcept;
  ForwardList &operator=(std::initializer_list< T > initializerList);
  T front();
  const T &front() const;
  const_iterator before_begin() const;
  iterator before_begin();
  const_iterator cbefore_begin() const;
  const_iterator begin() const;
  iterator begin();
  const_iterator cbegin() const;
  const_iterator end() const;
  iterator end();
  const_iterator cend() const;
  bool empty() const;
  void clear();
  iterator insert_after(const_iterator position, const T &value);
  void insert_after(const_iterator position, size_t count, const T &value);
  void insert_after(iterator position, std::initializer_list< T > initializerList);
  iterator insert_after(const_iterator position, T &&value);
  template< class InputIterator >
  void insert_after(const_iterator position, InputIterator first, InputIterator last);
  iterator emplace_after(const_iterator position, T &&value);
  iterator erase_after(const_iterator position);
  iterator erase_after(const_iterator first, const_iterator last);
  void push_front(const T &value);
  void push_front(T &&value);
  void emplace_front(T &&value);
  void pop_front();
  void resize(size_t newSize);
  void resize(size_t newSize, const T &value);
  void swap(ForwardList &rhs);
  void splice_after(const_iterator position, ForwardList &source);
  void splice_after(const_iterator position, ForwardList &&source);
  void splice_after(const_iterator position, ForwardList &source, const_iterator iterator);
  void splice_after(const_iterator position, ForwardList &&source, const_iterator iterator);
  void splice_after(const_iterator position, ForwardList &source, const_iterator first, const_iterator last);
  void splice_after(const_iterator position, ForwardList &&source, const_iterator first, const_iterator last);
  void remove(const T &value);
  template< class Predicate >
  void remove_if(Predicate pred);
  void reverse();
private:
  details::ListNode< T > *head_;
  details::ListNode< T > *tail_;
  details::ListNode< T > listNode;
};
template< typename T >
void ForwardList< T >::splice_after(const_iterator position, ForwardList &source)
{
  splice_after(position, std::move(source), source.begin(), source.end());
}
template< typename T >
void ForwardList< T >::splice_after(const_iterator position, ForwardList &&source)
{
  splice_after(position, std::move(source), source.begin(), source.end());
}
template< typename T >
void ForwardList< T >::splice_after(const_iterator position, ForwardList &source, const_iterator iterator)
{
  splice_after(position, std::move(source), iterator, std::next(iterator));
}
template< typename T >
void ForwardList< T >::splice_after(const_iterator position, ForwardList &&source, const_iterator iterator)
{
  splice_after(position, std::move(source), iterator, std::next(iterator));
}
template< typename T >
void
ForwardList< T >::splice_after(const_iterator position, ForwardList &source, const_iterator first, const_iterator last)
{
  splice_after(position, std::move(source), first, last);
}
template< typename T >
void
ForwardList< T >::splice_after(const_iterator position, ForwardList &&source, const_iterator first, const_iterator last)
{
  if (first == last)
  {
    return;
  }
  details::ListNode< T > *posNode = position.node;
  details::ListNode< T > *afterPosNode = posNode->next;
  details::ListNode< T > *sourceFirstNode = first.node;
  details::ListNode< T > *sourceLastNode = last.node;
  details::ListNode< T > *sourceLastNodeNext = sourceLastNode;
  while (sourceLastNodeNext->next != nullptr && sourceLastNodeNext->next != sourceLastNode)
  {
    sourceLastNodeNext = sourceLastNodeNext->next;
  }
  sourceLastNodeNext->next = afterPosNode;
  sourceFirstNode->next = sourceLastNode->next;
  posNode->next = sourceFirstNode;
  sourceLastNode->next = nullptr;
  if (source.head == sourceLastNode)
  {
    source.head = nullptr;
  }
}
template< typename T >
void ForwardList< T >::remove(const T &value)
{
  struct EqualToValue
  {
    explicit EqualToValue(const T &v):
      val(v)
    {
    }
    bool operator()(const T &element) const
    {
      return element == val;
    }
    const T &val;
  };
  EqualToValue pred(value);
  remove_if(pred);
}
template< typename T >
template< class Predicate >
void ForwardList< T >::remove_if(Predicate pred)
{
  details::ListNode< T > *current = head_;
  details::ListNode< T > *previous = nullptr;
  while (current != nullptr)
  {
    if (pred(current->data_))
    {
      if (previous != nullptr)
      {
        previous->next_ = current->next_;
        delete current;
        current = previous->next_;
      }
      else
      {
        head_ = current->next_;
        delete current;
        current = head_;
      }
    }
    else
    {
      previous = current;
      current = current->next_;
    }
  }
}
template< typename T >
void ForwardList< T >::resize(size_t newSize, const T &value)
{
  if (newSize == 0)
  {
    clear();
    return;
  }
  size_t currentSize = 0;
  auto it = begin();
  auto prev = before_begin();
  while (currentSize < newSize && it != end())
  {
    ++currentSize;
    ++it;
    ++prev;
  }
  if (currentSize == newSize)
  {
    erase_after(prev, end());
  }
  else if (currentSize < newSize)
  {
    while (currentSize < newSize)
    {
      emplace_after(prev, value);
      ++currentSize;
      ++prev;
    }
  }
}
template< typename T >
void ForwardList< T >::resize(size_t newSize)
{
  resize(newSize, T());
}
template< typename T >
typename ForwardList< T >::const_iterator ForwardList< T >::cbegin() const
{
  return const_iterator(head_);
}
template< typename T >
typename ForwardList< T >::const_iterator ForwardList< T >::cbefore_begin() const
{
  return const_iterator(const_cast<details::ListNode< T > *>(head_));
}
template< typename T >
typename ForwardList< T >::const_iterator ForwardList< T >::cend() const
{
  if (head_ == nullptr)
  {
    return nullptr;
  }
  details::ListNode< T > *node = head_;
  while (node->next_ != nullptr)
  {
    node = node->next_;
  }
  return node->next_;
}
template< typename T >
void ForwardList< T >::pop_front()
{
  if (head_ != nullptr)
  {
    details::ListNode< T > *toRemove = head_;
    head_ = head_->next_;
    delete toRemove;
  }
}
template< typename T >
void ForwardList< T >::emplace_front(T &&value)
{
  head_ = new details::ListNode< T >{std::forward< T >(value), head_};
}
template< typename T >
typename ForwardList< T >::iterator
ForwardList< T >::erase_after(ForwardList::const_iterator first, ForwardList::const_iterator last)
{
  if (first == last || first == end())
  {
    return iterator{};
  }
  if (first == before_begin())
  {
    auto it = begin();
    while (it != end() && it != last)
    {
      it = erase_after(before_begin());
    }
    return it;
  }
  auto pos = head_;
  while (pos->next_ != nullptr && pos->next_ != first)
  {
    pos = pos->next_;
  }
  auto it = iterator{pos->next_};
  while (it != end() && it != last)
  {
    it = erase_after(pos);
  }
  return it;
}
template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::erase_after(ForwardList< T >::const_iterator position)
{
  auto nextIt = position.current_->next_;
  if (nextIt)
  {
    position.current_->next_ = nextIt->next_;
    delete nextIt;
  }
  return ForwardList< T >::iterator(position.current_->next_);
}
template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::emplace_after(ForwardList::const_iterator position, T &&value)
{
  auto newNode = new details::ListNode< T >(std::forward< T >(value));
  newNode->next_ = position.current_->next_;
  position.current_->next_ = newNode;
  return ForwardList< T >::iterator(newNode);
}
template< typename T >
template< class InputIterator >
void ForwardList< T >::insert_after(ForwardList::const_iterator position, InputIterator first, InputIterator last)
{
  while (first != last)
  {
    position = ForwardList< T >::insert_after(position, *first);
    ++first;
    ++position;
  }
}
template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::insert_after(ForwardList::const_iterator position, T &&value)
{
  return ForwardList< T >::insert_after(position, std::move(value));
}
template< typename T >
void ForwardList< T >::insert_after(const ForwardList::iterator position, std::initializer_list< T > initializerList)
{
  for (const T &value: initializerList)
  {
    position = ForwardList< T >::insert_after(position, value);
    ++position;
  }
}
template< typename T >
void ForwardList< T >::insert_after(ForwardList::const_iterator position, size_t count, const T &value)
{
  for (size_t i = 0; i < count; ++i)
  {
    position = ForwardList< T >::insert_after(position, value);
  }
}
template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::insert_after(ForwardList::const_iterator position, const T &value)
{
  return ForwardList< T >::insert_after(position, value);
}
template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::end()
{
  return ForwardList< T >::end();
}
template< typename T >
typename ForwardList< T >::const_iterator ForwardList< T >::end() const
{
  return ForwardList< T >::cend();
}
template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::begin()
{
  return ForwardList< T >::begin();
}
template< typename T >
typename ForwardList< T >::const_iterator ForwardList< T >::begin() const
{
  return ForwardList< T >::cbegin();
}
template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::before_begin()
{
  return ForwardList< T >::before_begin();
}
template< typename T >
typename ForwardList< T >::const_iterator ForwardList< T >::before_begin() const
{
  return ForwardList< T >::cbefore_begin();
}
template< typename T >
const T &ForwardList< T >::front() const
{
  if (head_ == nullptr)
  {
    throw std::out_of_range("List is empty.");
  }
  return head_->data_;
}
template< typename T >
ForwardList< T >::~ForwardList()
{
  clear();
}
template< typename T >
T ForwardList< T >::front()
{
  if (head_ == nullptr)
  {
    throw std::out_of_range("List is empty.");
  }
  return head_->data_;
}
template< typename T >
ForwardList< T > &ForwardList< T >::operator=(const ForwardList &rhs)
{
  if (this != &rhs)
  {
    ForwardList temp(rhs);
    swap(temp);
  }
  return *this;
}
template< typename T >
ForwardList< T > &ForwardList< T >::operator=(ForwardList< T > &&rhs)
noexcept
{
  if (this != &rhs)
  {
    clear();
    head_ = rhs.head_;
    rhs.
      head_ = nullptr;
  }
  return *this;
}
template< typename T >
ForwardList< T > &ForwardList< T >::operator=(std::initializer_list< T > initializerList)
{
  ForwardList temp(initializerList);
  swap(temp);
  return *this;
}
template< typename T >
void ForwardList< T >::reverse()
{
  if (head_ != nullptr)
  {
    details::ListNode< T > *previous = nullptr;
    details::ListNode< T > *current = head_;
    details::ListNode< T > *next = nullptr;
    while (current != nullptr)
    {
      next = current->next;
      current->next = previous;
      previous = current;
      current = next;
    }
    head_ = previous;
  }
}
template< typename T >
void ForwardList< T >::clear()
{
  details::clear(head_);
  head_ = nullptr;
}
template< typename T >
bool ForwardList< T >::empty() const
{
  return head_ == nullptr;
}
template< typename T >
void ForwardList< T >::push_front(const T &value)
{
  head_ = new details::ListNode< T >{value, head_};
}
template< typename T >
void ForwardList< T >::push_front(T &&value)
{
  head_ = new details::ListNode< T >{std::move(value), head_};
}
template< typename T >
void ForwardList< T >::swap(ForwardList &rhs)
{
  std::swap(head_, rhs.head_);
}
template< typename T >
ForwardList< T >::ForwardList():
  head_(nullptr)
{
}
template< typename T >
ForwardList< T >::ForwardList(const ForwardList &rhs):
  ForwardList()
{
  for (auto it = rhs.begin(); it != rhs.end(); ++it)
  {
    push_front(*it);
  }
}
template< typename T >
ForwardList< T >::ForwardList(ForwardList &&rhs)
noexcept:
  head_(rhs.head_)
{
  rhs.
    head_ = nullptr;
}
template< typename T >
ForwardList< T >::ForwardList(std::initializer_list< T > initializerList):
  ForwardList()
{
  if (initializerList.size() == 0)
  {
    throw std::runtime_error("Cannot initialize empty list.");
  }
  for (const T &value: initializerList)
  {
    push_front(value);
  }
}
#endif
