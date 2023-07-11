#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>

#include <list.hpp>
#include "forwardlistiterator.hpp"
#include "forwardlistconstiterator.hpp"

template< typename T >
class ForwardList
{
  public:
    using iterator = ForwardListIterator< T >;
    using const_iterator = ForwardListConstIterator< T >;
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    bool empty() const;
    size_t max_size() const noexcept;
    void clear();
    iterator insert_after(const_iterator pos, const T& value);
    iterator insert_after(const_iterator pos, T&& value );
    iterator insert_after(const_iterator pos, size_t count, const T& value );
    iterator insert_after(const_iterator pos, iterator first, iterator last );
    template< typename... Args >
    iterator emplace_after(const_iterator pos, Args&&... args);
    iterator erase_after(const_iterator pos);
    iterator erase_after(const_iterator first, const_iterator last);
    void push_front(const T& value);
    void push_front(T&& value);
    template< typename... Args >
    void emplace_front(Args && ... args);
    void pop_front();
    void resize(size_t count);
    void resize(size_t count, const T& value);
    void swap(ForwardList< T >& other);
    List< T >* head_;
};

template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::begin() noexcept
{
  return iterator(head_);
}

template< typename T >
typename ForwardList< T >::const_iterator ForwardList< T >::begin() const noexcept
{
  return cbegin();
}

template< typename T >
typename ForwardList< T >::const_iterator ForwardList< T >::cbegin() const noexcept
{
  return const_iterator(head_);
}
template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::end() noexcept
{
  return iterator(nullptr);
}

template< typename T >
typename ForwardList< T >::const_iterator ForwardList< T >::end() const noexcept
{
  return cend();
}

template< typename T >
typename ForwardList< T >::const_iterator ForwardList< T >::cend() const noexcept
{
  return const_iterator(nullptr);
}

template< typename T >
bool ForwardList< T >::empty() const
{
  return head_ == nullptr;
}

template< typename T >
size_t ForwardList< T >::max_size() const noexcept
{
  size_t size = 0;
  List< T >* temp = head_;
  while (temp)
  {
    temp = temp->next_;
    size++;
  }
  return size;
}

template< typename T >
void ForwardList< T >::clear()
{
  while(head_->next_ != nullptr)
  {
    List< T >* temp = head_->next_;
    delete head_;
    head_ = temp;
  }
}

template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, const T& value)
{
  List< T >* temp = new List< T >();
  temp->data_ = value;
  List< T >* cur = const_cast< List< T >* >(pos.ptr_);
  temp->next_ = cur->next_;
  cur->next_ = temp;
  return iterator(temp);
}

template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, T&& value)
{
  return insert_after(pos, value);
}

template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, size_t count, const T& value)
{
  iterator temp;
  for (size_t i = 0; i < count; i++)
  {
    temp = insert_after(pos, value);
    pos++;
  }
  return temp;
}

template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, iterator first, iterator last)
{
  iterator temp;
  while (first != last)
  {
    temp = insert_after(pos, first.ptr_->data_);
    first++;
  }
  return temp;
}

template< typename T >
template< typename... Args >
typename ForwardList< T >::iterator ForwardList< T >::emplace_after(const_iterator pos, Args&&... args)
{
  List< T >* temp = new List< T >(std::forward<Args>(args)...);
  List< T >* cur = const_cast< List< T >* >(pos.ptr_);
  temp->next_ = cur->next_;
  cur->next_ = temp;
  return iterator(temp);
}

template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::erase_after(const_iterator pos)
{
  if (!(pos.ptr_ || pos.ptr_->next_))
  {
    return end();
  }

  List< T >* cur = const_cast< List< T >* >(pos.ptr_);
  List< T >* temp = cur;
  temp = temp->next_->next_;
  delete cur->next_;
  cur->next_ = temp;
  return iterator(cur);
}

template< typename T >
typename ForwardList< T >::iterator ForwardList< T >::erase_after(const_iterator first, const_iterator last)
{
  while ((first.ptr_->next_ != last.ptr_) && first.ptr_->next_)
  {
    erase_after(first);
  }
  return iterator(const_cast< List< T >* >(last.ptr_));
}

template< typename T >
void ForwardList< T >::push_front(const T& value)
{
  List< T >* temp = new List< T >();
  temp->data_ = value;
  temp->next_ = head_;
  head_ = temp;
}

template< typename T >
void ForwardList< T >::push_front(T&& value)
{
  push_front(value);
}

template< typename T >
template< typename... Args >
void ForwardList< T >::emplace_front(Args && ... args)
{
  List< T >* temp = new List< T >(std::forward<Args>(args)...);
  temp->next_ = head_;
  head_ = temp;
}

template< typename T >
void ForwardList< T >::pop_front()
{
  if (empty())
  {
    throw std::logic_error("empty list");
  }
  List< T >* temp = head_;
  head_ = head_->next_;
  delete temp;
}

template< typename T >
void ForwardList< T >::resize(size_t count, const T& value)
{
  size_t cur_size = max_size();
  if (count == cur_size)
  {
    return;
  }

  else if (count < cur_size)
  {
    auto iter_to_erase = cbegin();
    for (size_t i = 1; i < count; i++)
    {
      iter_to_erase++;
    }
    erase_after(iter_to_erase, cend());
  }

  else
  {
    auto iter_to_insert = cbegin();
    for (size_t i = 1; i < cur_size; i++)
    {
      iter_to_insert++;
    }
    insert_after(iter_to_insert, count - cur_size, value);
  }
}

template< typename T >
void ForwardList< T >::resize(size_t count)
{
  resize(count, T());
}

template< typename T >
void ForwardList< T >::swap(ForwardList< T >& other)
{
  std::swap(head_, other.head_);
}

template< typename T >
bool operator==(const ForwardList< T >& lhs, const ForwardList< T >& rhs)
{
  if (lhs.empty() && rhs.empty())
  {
    return true;
  }

  else if (lhs.empty() || rhs.empty())
  {
    return false;
  }

  auto lhs_begin = lhs.cbegin();
  auto lhs_end = lhs.cend();
  auto rhs_begin = rhs.cbegin();
  auto rhs_end = rhs.cend();
  while ((lhs_begin != lhs_end) && (rhs_begin != rhs_end))
  {
    if (*lhs_begin != *rhs_end)
    {
      return false;
    }
    lhs_begin++;
    rhs_begin++;
  }
  return true;
}

template < typename T >
bool operator!=(const ForwardList< T >& lhs, const ForwardList< T >& rhs)
{
  return !(lhs == rhs);
}

#endif
