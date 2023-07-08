#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <tuple>
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
  ForwardList(const ForwardList &other);
  ForwardList(ForwardList &&other) noexcept;
  ForwardList(std::initializer_list< T > initializerList);
  ~ForwardList();
  ForwardList &operator=(const ForwardList &other);
  ForwardList &operator=(ForwardList &&other) noexcept;
  ForwardList &operator=(std::initializer_list< T > initializerList);
  T front();
  const T &front() const;
  iterator before_begin() const;
  iterator before_begin();
  const_iterator cbefore_begin() const;
  iterator begin() const;
  iterator end();
  const_iterator cbegin() const;
  iterator end() const;
  const_iterator cend() const;
  bool empty() const;
  void clear();
  iterator insert_after(iterator position, const T &value);
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
  template< class ... Args >
  iterator emplace_front(Args &&... args);
  void pop_front();
  void resize(size_t newSize);
  void resize(size_t newSize, const T &value);
  void swap(ForwardList &other);
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
  details::ListNode< T > *begin_;
private:
  details::ListNode< T > *end_;
  details::ListNode< T > *fakeNode_;
  size_t size_;
  details::ListNode< T > *initFake();
  void copy(const ForwardList< T > &other);
  void push_back(const T &value);
};
template< typename T >
void ForwardList< T >::push_back(const T &value)
{
  std::cout << "!\n";
  details::ListNode< T > *node = new details::ListNode< T >(value);
  if (!begin_)
  {
    begin_ = node;
    fakeNode_->next_ = begin_;
  }
  else if (!end_)
  {
    end_ = node;
    begin_->next_ = end_;
  }
  else
  {
    end_->next_ = node;
    end_ = node;
  }
  ++size_;
}
template< typename T >
void ForwardList< T >::copy(const ForwardList< T > &other)
{
  auto tmp = details::copy(other.begin_);
  begin_ = std::get< 0 >(tmp);
  end_ = std::get< 1 >(tmp);
  fakeNode_->next_ = begin_;
}
template< typename T >
details::ListNode< T > *ForwardList< T >::initFake()
{
  void *nodeMemory = ::operator new(sizeof(details::ListNode< T >));
  details::ListNode< T > *newNode = static_cast< details::ListNode< T > * >(nodeMemory);
  newNode->next_ = nullptr;
  return newNode;
}
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
  auto posNode = position.ptr_;
  auto afterPosNode = posNode->next;
  auto sourceFirstNode = first.ptr_;
  auto sourceLastNode = last.ptr_;
  auto sourceLastNodeNext = sourceLastNode;
  while (sourceLastNodeNext->next && sourceLastNodeNext->next != sourceLastNode)
  {
    sourceLastNodeNext = sourceLastNodeNext->next;
  }
  sourceLastNodeNext->next = nullptr;
  sourceFirstNode->next = sourceLastNode->next;
  posNode->next = sourceFirstNode;
  sourceLastNode->next = afterPosNode;
  if (source.begin_ == sourceLastNode)
  {
    source.begin_ = nullptr;
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
  details::ListNode< T > *current = begin_;
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
        begin_ = current->next_;
        delete current;
        current = begin_;
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
  auto prev = cbefore_begin();
  while (currentSize < newSize && it != end())
  {
    ++currentSize;
    ++it;
    ++prev;
  }
  if (currentSize == newSize)
  {
    erase_after(prev, cend());
  }
  else if (currentSize < newSize)
  {
    while (currentSize < newSize)
    {
      emplace_after(prev, T(value));
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
ConstForwardListIterator< T > ForwardList< T >::cbegin() const
{
  return ConstForwardListIterator< T >(begin_);
}
template< typename T >
ConstForwardListIterator< T > ForwardList< T >::cbefore_begin() const
{
  return ConstForwardListIterator< T >(fakeNode_);
}
template< typename T >
ConstForwardListIterator< T > ForwardList< T >::cend() const
{
  return ConstForwardListIterator< T >(nullptr);
}
template< typename T >
void ForwardList< T >::pop_front()
{
  erase_after(cbefore_begin());
}
template< typename T >
template< class ... Args >
ForwardListIterator< T > ForwardList< T >::emplace_front(Args &&... args)
{
  push_front(T(std::forward< Args >(args)...));
  return begin();
}
template< typename T >
ForwardListIterator< T > ForwardList< T >::erase_after(ConstForwardListIterator< T > position)
{
  auto nextIt = position.head_->next_;
  if (nextIt)
  {
    position.head_->next_ = nextIt->next_;
    delete nextIt;
  }
  if (position.head_->next_)
  {
    return ForwardListIterator< T >(position.head_->next_);
  }
  else
  {
    return end();
  }
}
template< typename T >
ForwardListIterator< T >
ForwardList< T >::erase_after(ConstForwardListIterator< T > first, ConstForwardListIterator< T > last)
{
  if (first == last || first == cend() || empty())
  {
    return ForwardListIterator< T >();
  }
  if (first == cbefore_begin())
  {
    auto it = begin();
    while (it != end() && it != ForwardListIterator< T >(last))
    {
      it = erase_after(cbefore_begin());
    }
    return it;
  }
  auto pos = begin_;
  while (pos->next_ != nullptr && pos->next_ != first.head_)
  {
    pos = pos->next_;
  }
  if (pos->next_ == nullptr)
  {
    return end();
  }
  auto it = ForwardListIterator< T >{pos->next_};
  while (it != end() && it != ForwardListIterator< T >(last))
  {
    it = erase_after(ConstForwardListIterator< T >(pos));
  }
  return it;
}
template< typename T >
ForwardListIterator< T > ForwardList< T >::emplace_after(ConstForwardListIterator< T > position, T &&value)
{
  return insert_after(position, std::forward< T >(value));
}
template< typename T >
template< class InputIterator >
void ForwardList< T >::insert_after(ConstForwardListIterator< T > position, InputIterator first, InputIterator last)
{
  while (first != last)
  {
    position = insert_after(position, *first);
    ++first;
    ++position;
  }
}
template< typename T >
ForwardListIterator< T > ForwardList< T >::insert_after(ConstForwardListIterator< T > position, T &&value)
{
  return insert_after(position, std::move(value));
}
template< typename T >
void ForwardList< T >::insert_after(ForwardListIterator< T > position, std::initializer_list< T > initializerList)
{
  for (const T &value: initializerList)
  {
    insert_after(position, value);
    ++position;
  }
}
template< typename T >
void ForwardList< T >::insert_after(ConstForwardListIterator< T > position, size_t count, const T &value)
{
  for (size_t i = 0; i < count; ++i)
  {
    position = insert_after(position, value);
    ++position;
  }
}
template< typename T >
ForwardListIterator< T >
ForwardList< T >::insert_after(ForwardListIterator< T > position, const T &value)
{
  details::ListNode< T > *node = new details::ListNode< T >{value, begin_};
  node->next_ = position.head_->next_;
  position.head_->next_ = node;
  if (end_ == position.head_)
  {
    end_ = node;
  }
  ++size_;
  return ForwardListIterator< T >(node);
}
template< typename T >
ForwardListIterator< T > ForwardList< T >::end()
{
  return ForwardListIterator< T >(nullptr);
}
template< typename T >
ForwardListIterator< T > ForwardList< T >::end() const
{
  return ForwardListIterator< T >(nullptr);
}
template< typename T >
ForwardListIterator< T > ForwardList< T >::begin() const
{
  return ForwardListIterator< T >(begin_);
}
template< typename T >
ForwardListIterator< T > ForwardList< T >::before_begin()
{
  return ForwardListIterator< T >(fakeNode_);
}
template< typename T >
ForwardListIterator< T > ForwardList< T >::before_begin() const
{
  return ForwardListIterator< T >(fakeNode_);
}
template< typename T >
const T &ForwardList< T >::front() const
{
  return begin_->data_;
}
template< typename T >
T ForwardList< T >::front()
{
  return begin_->data_;
}
template< typename T >
ForwardList< T >::~ForwardList()
{
  clear();
  ::operator delete(fakeNode_);
}
template< typename T >
ForwardList< T > &ForwardList< T >::operator=(const ForwardList &other)
{
  if (this != std::addressof(other))
  {
    ForwardList tmp(other);
    swap(tmp);
  }
  return *this;
}
template< typename T >
ForwardList< T > &ForwardList< T >::operator=(ForwardList< T > &&other)
noexcept
{
  if (this != std::addressof(other))
  {
    clear();
    begin_ = other.begin_;
    end_ = other.end_;
    fakeNode_->next_ = begin_;
    size_ = other.size_;
    other.begin_ = nullptr;
    other.end_ = nullptr;
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
  if (begin_ != nullptr)
  {
    details::ListNode< T > *previous = nullptr;
    details::ListNode< T > *current = begin_;
    details::ListNode< T > *next = nullptr;
    while (current != nullptr)
    {
      next = current->next_;
      current->next_ = previous;
      previous = current;
      current = next;
    }
    begin_ = previous;
  }
}
template< typename T >
void ForwardList< T >::clear()
{
  details::clear(begin_);
  begin_ = nullptr;
}
template< typename T >
bool ForwardList< T >::empty() const
{
  return begin_ == nullptr;
}
template< typename T >
void ForwardList< T >::push_front(const T &value)
{
  begin_ = new details::ListNode< T >(value, begin_);
}
template< typename T >
void ForwardList< T >::push_front(T &&value)
{
  begin_ = new details::ListNode< T >(std::move(value), begin_);
}
template< typename T >
void ForwardList< T >::swap(ForwardList &other)
{
  std::swap(begin_, other.begin_);
  std::swap(end_, other.end_);
  std::swap(fakeNode_, other.fakeNode_);
  size_ = other.size_;
}
template< typename T >
ForwardList< T >::ForwardList():
  begin_(nullptr),
  end_(nullptr),
  fakeNode_(initFake()),
  size_(0)
{
}
template< typename T >
ForwardList< T >::ForwardList(const ForwardList &other):
  ForwardList()
{
  copy(other);
}
template< typename T >
ForwardList< T >::ForwardList(ForwardList &&other) noexcept:
  begin_(std::move(other.begin_)),
  end_(std::move(other.end_)),
  fakeNode_(std::move(other.fakeNode_)),
  size_(other.size_)
{
  other.begin_ = nullptr;
  other.end_ = nullptr;
  other.fakeNode_ = nullptr;
  other.size_ = 0;
}
template< typename T >
ForwardList< T >::ForwardList(std::initializer_list< T > initializerList):
  ForwardList()
{
  fakeNode_->next_ = nullptr;
  if (initializerList.size() == 0)
  {
    throw std::runtime_error("Cannot initialize empty list.");
  }
  for (const T &value: initializerList)
  {
    push_back(value);
  }
}
#endif
