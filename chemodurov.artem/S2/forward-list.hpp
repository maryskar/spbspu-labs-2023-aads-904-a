#ifndef S2_FORWARD_LIST_HPP
#define S2_FORWARD_LIST_HPP
#include <initializer_list>
#include <iterator>
#include <functional>
#include "const-forward-iterator.hpp"
#include "forward-iterator.hpp"

namespace chemodurov
{
  template< typename T >
  class ForwardList
  {
   public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = ForwardIterator< T >;
    using const_iterator = ConstForwardIterator< T >;
    using this_t = ForwardList< T >;
    ForwardList();
    ForwardList(const this_t & rhs);
    ForwardList(this_t && rhs);
    ForwardList(std::initializer_list< T > init);
    template< typename InputIt >
    ForwardList(InputIt first, InputIt last);
    ~ForwardList();
    this_t & operator=(const this_t & rhs);
    this_t & operator=(this_t && rhs);
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
    void clear() noexcept;
    iterator insert_after(const_iterator pos, const_reference value);
    iterator insert_after(const_iterator pos, T && value);
    iterator insert_after(const_iterator pos, size_type count, const_reference value);
    template< typename InputIt >
    iterator insert_after(const_iterator pos, InputIt first, InputIt last);
    iterator insert_after(const_iterator pos, std::initializer_list< T > init);
    template< typename... Args >
    iterator emplace_after(const_iterator pos, Args && ... args);
    iterator erase_after(const_iterator pos);
    iterator erase_after(const_iterator first, const_iterator last);
    void push_front(const_reference value);
    void push_front(T && value);
    template< typename... Args >
    void emplace_front(Args && ... args);
    void pop_front() noexcept;
    void safe_pop_front();
    void resize(size_type count);
    void resize(size_type count, const_reference value);
    void swap(this_t & other) noexcept;
    void splice_after(const_iterator pos, this_t & other);
    void splice_after(const_iterator pos, this_t && other);
    void splice_after(const_iterator pos, this_t & other, const_iterator it);
    void splice_after(const_iterator pos, this_t && other, const_iterator it);
    void splice_after(const_iterator pos, this_t & other, const_iterator first, const_iterator last);
    void splice_after(const_iterator pos, this_t && other, const_iterator first, const_iterator last);
    void remove(const_reference value);
    template< typename UnaryPredicate >
    void remove_if(UnaryPredicate p);
    void reverse() noexcept;
   private:
    iterator fake_;
    iterator last_;
    void moveLastTo(const_iterator it);
  };

  template< typename T >
  ForwardList< T >::ForwardList():
   fake_(static_cast< detail::List< T > * >(::operator new (sizeof(detail::List< T >)))),
   last_(fake_)
  {
    fake_.node_->next = fake_.node_;
  }

  template< typename T >
  bool ForwardList< T >::empty() const noexcept
  {
    return fake_.node_->next == fake_.node_;
  }

  template< typename T >
  void ForwardList< T >::clear() noexcept
  {
    last_.node_->next = nullptr;
    detail::deleteList(fake_.node_->next);
    fake_.node_->next = fake_.node_;
  }

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    clear();
    ::operator delete(fake_.node_);
  }

  template< typename T >
  ForwardList< T >::ForwardList(const this_t & rhs):
   ForwardList(rhs.begin(), rhs.end())
  {}

  template< typename T >
  ForwardList< T >::ForwardList(this_t && rhs):
   ForwardList()
  {
    fake_.node_->next = rhs.fake_.node_->next;
    last_ = rhs.last_;
    rhs.fake_.node_->next = rhs.fake_.node_;
    rhs.last_ = rhs.fake_;
    last_.node_->next = fake_.node_;
  }

  template< typename T >
  ForwardList< T >::ForwardList(std::initializer_list< T > init):
   ForwardList(init.begin(), init.end())
  {}

  template< typename T >
  template< typename InputIt >
  ForwardList< T >::ForwardList(InputIt first, InputIt last):
   ForwardList()
  {
    iterator it = before_begin();
    while (first != last)
    {
      it = insert_after(it, *(first++));
    }
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::before_begin() noexcept
  {
    return fake_;
  }

  template< typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::before_begin() const noexcept
  {
    return cbefore_begin();
  }

  template< typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::cbefore_begin() const noexcept
  {
    return const_iterator(fake_);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::begin() noexcept
  {
    return iterator(fake_.node_->next);
  }

  template< typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::cbegin() const noexcept
  {
    return const_iterator(fake_.node_->next);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::end() noexcept
  {
    return fake_;
  }

  template< typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::end() const noexcept
  {
    return cend();
  }

  template< typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::cend() const noexcept
  {
    return const_iterator(fake_);
  }

  template< typename T >
  ForwardList< T > & ForwardList< T >::operator=(const this_t & rhs)
  {
    if (*this == rhs)
    {
      return *this;
    }
    this_t temp(rhs);
    clear();
    swap(temp);
    return *this;
  }

  template< typename T >
  ForwardList< T > & ForwardList< T >::operator=(this_t && rhs)
  {
    if (*this == rhs)
    {
      return *this;
    }
    clear();
    swap(rhs);
    return *this;
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, const_reference value)
  {
    pos.node_->next = new detail::List< T >{value, pos.node_->next};
    moveLastTo(++pos);
    return iterator(pos.node_);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, T && value)
  {
    pos.node_->next = new detail::List< T >{std::move(value), pos.node_->next};
    moveLastTo(++pos);
    return iterator(pos.node_);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, size_type count, const_reference value)
  {
    for (size_type i = 0; i < count; ++i)
    {
      pos = insert_after(pos, value);
    }
    return iterator(pos.node_);
  }

  template< typename T >
  template< typename InputIt >
  typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, InputIt first, InputIt last)
  {
    for (first; first != last; ++first)
    {
      pos = insert_after(pos, *first);
    }
    return iterator(pos.node_);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, std::initializer_list< T > init)
  {
    return insert_after(pos, init.begin(), init.end());
  }

  template< typename T >
  template< typename... Args >
  typename ForwardList< T >::iterator ForwardList< T >::emplace_after(const_iterator pos, Args && ... args)
  {
    pos.node_->next = new detail::List< T >{T(args...), pos.node_->next};
    moveLastTo(++pos);
    return iterator(pos.node_);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::erase_after(const_iterator pos)
  {
    if (empty())
    {
      return end();
    }
    if (pos == last_)
    {
      erase_after(fake_);
    }
    detail::List< T > * temp = pos.node_->next->next;
    delete pos.node_->next;
    pos.node_->next = temp;
    moveLastTo(pos);
    return iterator(temp);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::erase_after(const_iterator first, const_iterator last)
  {
    while (first != last)
    {
      erase_after(first);
    }
    return iterator(last.node_);
  }

  template< typename T >
  void ForwardList< T >::push_front(const_reference value)
  {
    insert_after(cbefore_begin(), value);
  }

  template< typename T >
  void ForwardList< T >::push_front(T && value)
  {
    insert_after(cbefore_begin(), std::move(value));
  }

  template< typename T >
  template< typename... Args >
  void ForwardList< T >::emplace_front(Args && ... args)
  {
    emplace_after(cbefore_begin(), std::move(args...));
  }

  template< typename T >
  void ForwardList< T >::pop_front() noexcept
  {
    erase_after(cbefore_begin());
  }

  template< typename T >
  void ForwardList< T >::safe_pop_front()
  {
    if (empty())
    {
      throw std::invalid_argument("Empty forward list");
    }
    pop_front();
  }

  template< typename T >
  void ForwardList< T >::resize(size_type count, const_reference value)
  {
    iterator it = begin();
    iterator end = end();
    size_type size = 0;
    while (size < count && it != end)
    {
      ++size;
      ++it;
    }
    if (size == count && it == end)
    {
      return;
    }
    else if (size == count && it != end)
    {
      last_.node_->next = nullptr;
      detail::deleteList(it.node_);
    }
    else
    {
      last_ = insert_after(last_, count - size, value);
    }
  }

  template< typename T >
  void ForwardList< T >::resize(size_type count)
  {
    resize(count, T{});
  }

  template< typename T >
  void ForwardList< T >::swap(this_t & other) noexcept
  {
    std::swap(fake_, other.fake_);
    std::swap(last_, other.last_);
  }

  template< typename T >
  void ForwardList< T >::splice_after(const_iterator pos, this_t & other)
  {
    splice_after(pos, other, other.before_begin());
  }

  template< typename T >
  void ForwardList< T >::splice_after(const_iterator pos, this_t && other)
  {
    splice_after(pos, other);
  }

  template< typename T >
  void ForwardList< T >::splice_after(const_iterator pos, this_t & other, const_iterator it)
  {
    const_iterator moved_pos = pos;
    ++moved_pos;
    if (pos == it && moved_pos == it)
    {
      return;
    }
    detail::List< T > * temp = pos.node_->next;
    pos.node_->next = it.node_->next;
    other.last_.node_->next = temp;
    it.node_->next = other.fake_.node_;
    other.last_ = it;
  }

  template< typename T >
  void ForwardList< T >::splice_after(const_iterator pos, this_t && other, const_iterator it)
  {
    splice_after(pos, other, it);
  }

  template< typename T >
  void ForwardList< T >::splice_after(const_iterator pos, this_t & other, const_iterator first, const_iterator last)
  {
    detail::List< T > * temp = pos.node_->next;
    iterator moved_first = first;
    ++moved_first;
    iterator it = insert_after(pos, moved_first, last);
    it.node_->next = temp;
    first.node_->next = last.node_;
  }

  template< typename T >
  void ForwardList< T >::splice_after(const_iterator pos, this_t && other, const_iterator first, const_iterator last)
  {
    splice_after(pos, other, first, last);
  }

  template< typename T >
  void ForwardList< T >::remove(const_reference value)
  {
    remove_if(std::bind(std::equal< T >(), std::placeholders::_1, value));
  }

  template< typename T >
  template< typename UnaryPredicate >
  void ForwardList< T >::remove_if(UnaryPredicate p)
  {
    iterator end = end();
    iterator it = begin();
    if (p(it.node_->data))
    {
      erase_after(before_begin());
    }
    for (; it != end; ++it)
    {
      if (p(it.node_->next->data))
      {
        erase_after(it);
      }
    }
  }

  template< typename T >
  void ForwardList< T >::reverse() noexcept
  {
    iterator beg = begin();
    iterator reversed = beg;
    iterator end_ = end();
    for (iterator i = beg, j = ++(begin()); j != end_; i = j, ++j)
    {
      i.node_->next = reversed.node_;
      reversed = i;
    }
    last_.node_->next = reversed.node_;
    fake_.node_->next = last_.node_;
    last_ = beg;
  }

  template< typename T >
  void ForwardList< T >::moveLastTo(const_iterator it)
  {
    if (last_.node_->next != fake_.node_)
    {
      last_ = iterator(it.node_);
    }
  }

  template< typename T >
  bool operator==(const ForwardList< T > & lhs, const ForwardList< T > & rhs)
  {
    if (lhs.empty() && rhs.empty())
    {
      return true;
    }
    using cit_t = typename ForwardList< T >::const_iterator;
    cit_t l_it = lhs.cbegin();
    cit_t r_it = rhs.cbegin();
    const cit_t l_end = lhs.cend();
    const cit_t r_end = rhs.cend();
    for (; l_it != l_end && r_it != r_end; ++l_it, ++r_it)
    {
      if (*l_it != *r_it)
      {
        return false;
      }
    }
    return l_it == l_end && r_it == r_end;
  }

  template< typename T >
  bool operator!=(const ForwardList< T > & lhs, const ForwardList< T > & rhs)
  {
    return !(lhs == rhs);
  }
}

#endif
