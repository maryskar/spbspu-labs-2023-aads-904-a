#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include <iterator>
#include <initializer_list>
#include "forward_list_const_iterator.h"
#include "forward_list_iterator.h"
#include "../common/node.h"

namespace kryuchkova
{
  template< typename T >
  class ForwardList
  {
  public:
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

    this_t & operator=(const this_t & fwdlst);
    this_t & operator=(this_t && fwdlst);
    this_t & operator=(std::initializer_list< T > init);

    iterator insert_after(const_iterator pos, const T & val);
    iterator insert_after(const_iterator pos, T && val);
    iterator insert_after(const_iterator pos, std::size_t n, const T & val);
    iterator insert_after(const_iterator pos, std::initializer_list< T > init);
    template< typename InputIt >
    iterator insert_after(const_iterator pos, InputIt first, InputIt last);
    iterator erase_after(const_iterator pos);
    iterator erase_after(const_iterator first, const_iterator last);

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

    bool IsEmpty() const noexcept;
    void clear() noexcept;
    void push_front(const T & val);
    void push_front(T && val);
    void pop_front() noexcept;
    void resize(std::size_t count);
    void resize(std::size_t count, const T & val);
    void swap(this_t & other) noexcept;
    void splice_after(const_iterator pos, this_t & other);
    void splice_after(const_iterator pos, this_t && other);
    void splice_after(const_iterator pos, this_t & other, const_iterator iter);
    void splice_after(const_iterator pos, this_t && other, const_iterator iter);
    void splice_after(const_iterator pos, this_t & other, const_iterator first, const_iterator last);
    void splice_after(const_iterator pos, this_t && other, const_iterator first, const_iterator last);
    void remove(const T & val);
    void reverse() noexcept;

  private:
    iterator fake_;
    iterator last_;
  };

  template < typename T >
  ForwardList< T >::ForwardList():
    fake_(static_cast< Node< T > * >(::operator new (sizeof(Node< T >)))),
    last_(iterator(nullptr))
  {
    fake_.node_->next_ = nullptr;
  }

  template < typename T >
  bool ForwardList< T >::IsEmpty() const noexcept
  {
    return fake_.node_->next_ == nullptr;
  }

  template < typename T >
  void ForwardList< T >::clear() noexcept
  {
    if (IsEmpty())
    {
      return;
    }
    while (fake_.node_->next_ != nullptr)
    {
      Node< T > * temp = fake_.node_->next_;
      fake_.node_->next_ = temp->next_;
      delete temp;
    }
    fake_.node_->next_ = nullptr;
    last_.node_ = nullptr;
  }

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

  template < typename T >
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
    swap(rhs);
  }

  template< typename T >
  ForwardList< T >::ForwardList(std::initializer_list< T > init):
   ForwardList(init.begin(), init.end())
  {}


  template< typename T >
  ForwardList< T > & ForwardList< T >::operator=(const this_t & fwdlst)
  {
    if (this == std::addressof(fwdlst))
    {
      return *this;
    }
    this_t temp(fwdlst);
    clear();
    swap(temp);
    return *this;
  }

  template< typename T >
  ForwardList< T > & ForwardList< T >::operator=(this_t && fwdlst)
  {
    if (this == std::addressof(fwdlst))
    {
      return *this;
    }
    clear();
    swap(fwdlst);
    return *this;
  }

  template< typename T >
  ForwardList< T > & ForwardList< T >::operator=(std::initializer_list< T > init)
  {
    this_t temp(init);
    clear();
    swap(temp);
    return *this;
  }

  template< typename T >
  ForwardIterator< T > ForwardList< T >::insert_after(const_iterator pos, const T & val)
  {
    pos.node_->next_ = new Node< T >{val, pos.node_->next_};
    ++pos;
    return iterator(pos.node_);
  }

  template< typename T >
  ForwardIterator< T > ForwardList< T >::insert_after(const_iterator pos, T && val)
  {
    return insert_after(pos, val);
  }

  template< typename T >
  ForwardIterator< T > ForwardList< T >::insert_after(const_iterator pos, std::size_t n, const T & val)
  {
    for (std::size_t i = 0; i < n; ++i)
    {
      pos = insert_after(pos, val);
    }
    return iterator(pos.node_);
  }

  template< typename T >
  ForwardIterator< T > ForwardList< T >::insert_after(const_iterator pos, std::initializer_list< T > init)
  {
    return insert_after(pos, init.begin(), init.end());
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
  ForwardIterator< T > ForwardList< T >::erase_after(const_iterator pos)
  {
    if (pos == last_)
    {
      erase_after(fake_);
    }
    Node< T > * temp = pos.node_->next_->next_;
    if (pos.node_->next_ == last_.node_)
    {
      last_ = iterator(pos.node_);
    }
    delete pos.node_->next_;
    pos.node_->next_ = temp;
    return iterator(temp);
  }

  template< typename T >
  ForwardIterator< T > ForwardList< T >::erase_after(const_iterator first, const_iterator last)
  {
    while (first != last)
    {
      erase_after(first);
    }
    return iterator(last.node_);
  }

  template< typename T >
  ForwardIterator< T > ForwardList< T >::before_begin() noexcept
  {
    return fake_;
  }

  template< typename T >
  ConstForwardIterator< T > ForwardList< T >::before_begin() const noexcept
  {
    return cbefore_begin();
  }

  template< typename T >
  ConstForwardIterator< T > ForwardList< T >::cbefore_begin() const noexcept
  {
    return const_iterator(fake_);
  }

  template< typename T >
  ForwardIterator< T > ForwardList< T >::begin() noexcept
  {
    return iterator(fake_.node_->next);
  }

  template< typename T >
  ConstForwardIterator< T > ForwardList< T >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename T >
  ConstForwardIterator< T > ForwardList< T >::cbegin() const noexcept
  {
    return const_iterator(fake_.node_->next);
  }

  template< typename T >
  ForwardIterator< T > ForwardList< T >::end() noexcept
  {
    return fake_;
  }

  template< typename T >
  ConstForwardIterator< T > ForwardList< T >::end() const noexcept
  {
    return cend();
  }

  template< typename T >
  ConstForwardIterator< T > ForwardList< T >::cend() const noexcept
  {
    return const_iterator(fake_);
  }

  template< typename T >
  ForwardIterator< T > ForwardList< T >::last() noexcept
  {
    return last_;
  }

  template< typename T >
  ConstForwardIterator< T > ForwardList< T >::last() const noexcept
  {
    return clast();
  }

  template< typename T >
  ConstForwardIterator< T > ForwardList< T >::clast() const noexcept
  {
    return const_iterator(last_);
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
  void ForwardList< T >::splice_after(const_iterator pos, this_t & other, const_iterator iter)
  {
    const_iterator moved = pos;
    ++moved;
    if (pos == iter && moved == iter)
    {
      return;
    }
    Node< T > * temp = pos.node_->next_;
    pos.node_->next_ = iter.node_->next_;
    other.last_.node_->next_ = temp;
    iter.node_->next_ = other.fake_.node_;
    other.last_.node_ = iter.node_;
  }

  template< typename T >
  void ForwardList< T >::splice_after(const_iterator pos, this_t && other, const_iterator iter)
  {
    splice_after(pos, other, iter);
  }

  template< typename T >
  void ForwardList< T >::splice_after(const_iterator pos, this_t & other, const_iterator first, const_iterator last)
  {
    Node< T > * temp = pos.node_->next_;
    iterator moved_first;
    moved_first.node_ = first.node_;
    ++moved_first;
    iterator iter = insert_after(pos, moved_first, last);
    iter.node_->next_ = temp;
    first.node_->next_ = last.node_;
  }

  template< typename T >
  void ForwardList< T >::splice_after(const_iterator pos, this_t && other, const_iterator first, const_iterator last)
  {
    splice_after(pos, other, first, last);
  }

  template< typename T >
  void ForwardList< T >::push_front(const T & val)
  {
    insert_after(cbefore_begin(), val);
  }

  template< typename T >
  void ForwardList< T >::push_front(T && val)
  {
    insert_after(cbefore_begin(), std::move(val));
  }

  template< typename T >
  void ForwardList< T >::pop_front() noexcept
  {
    if (IsEmpty())
    {
      throw std::invalid_argument("Nothing to pop.");
    }
    erase_after(cbefore_begin());
  }

  template< typename T >
  void ForwardList< T >::resize(std::size_t count, const T & val)
  {
    iterator iter = begin();
    std::size_t size = 0;
    while (size < count && iter != end())
    {
      ++size;
      ++iter;
    }
    if (size == count && iter == end())
    {
      return;
    }
    else if (size == count && iter != end())
    {
      last_.node_->next_ = nullptr;
      deleteNode(iter.node_);
    }
    else
    {
      last_ = insert_after(last_, count - size, val);
    }
  }

  template< typename T >
  void ForwardList< T >::resize(std::size_t count)
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
  void ForwardList< T >::remove(const T & val)
  {
    iterator first = before_begin();
    iterator last = end();
    while(first.node_->next_ != last.node_)
    {
      if (first.node_->next_->data_ == val)
      {
        auto toDel = first.node_->next_;
        first.node_->next_ = first.node_->next_->next_;
        delete toDel;
      }
      ++first;
    }
  }

  template< typename T >
  void ForwardList< T >::reverse() noexcept
  {
    iterator begin_ = begin();
    iterator reversed = begin_;
    iterator end_ = end();
    for (iterator i = begin_, j = ++(begin()); j != end_; i = j, ++j)
    {
      i.node_->next_ = reversed.node_;
      reversed = i;
    }
    last_.node_->next_ = reversed.node_;
    fake_.node_->next_ = last_.node_;
    last_ = begin_;
  }

}

#endif
