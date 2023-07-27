#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <list.h>
#include "forwardIterator.h"
#include "constForwardIterator.h"
namespace fesenko
{
  template< typename T >
  class ForwardList
  {
   public:
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = ForwardIterator< T >;
    using const_iterator = ConstForwardIterator< T >;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using this_t = ForwardList< T >;
    ForwardList();
    ForwardList(const this_t &);
    ForwardList(this_t &&);
    this_t &operator=(const this_t &);
    this_t &operator=(this_t &&);
    ~ForwardList();
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
    reference front();
    const_reference front() const;
    iterator insert_after(const_iterator position, const value_type &);
    iterator insert_after(const_iterator position, value_type &&);
    iterator insert_after(const_iterator, size_type, const value_type &);
    void push_front(const value_type &);
    void push_front(value_type &&);
    iterator erase_after(const_iterator);
    iterator erase_after(const_iterator, const_iterator);
    void pop_front();
   private:
    List< T > *fakeNode_;
    List< T > *begin_;
    List< T > *end_;
    size_t size_;
  };

  template< typename T >
  ForwardList< T >::ForwardList():
    fakeNode_(static_cast< List< T > * >(::operator new (sizeof(List< T >)))),
    begin_(nullptr),
    end_(nullptr),
    size_(0)
  {
    fakeNode_->next = nullptr;
  }

  template< typename T >
  ForwardList< T >::ForwardList(const this_t &rhs):
    ForwardList()
  {
    copy(rhs);
  }

  template< typename T >
  ForwardList< T >::ForwardList(this_t &&rhs):
    ForwardList()
  {
    std::swap(fakeNode_, rhs.fakeNode_);
    std::swap(begin_, rhs.begin_);
    std::swap(end_, rhs.end_);
    std::swap(size_, rhs.size_);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::before_begin() noexcept
  {
    return iterator(fakeNode_);
  }

  template< typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::before_begin() const noexcept
  {
    return cbefore_begin();
  }

  template< typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::cbefore_begin() const noexcept
  {
    return const_iterator(fakeNode_);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::begin() noexcept
  {
    return iterator(begin_);
  }

  template< typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::cbegin() const noexcept
  {
    return const_iterator(begin_);
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
  bool ForwardList< T >::empty() const noexcept
  {
    return begin_ == nullptr;
  }

  template< typename T >
  void ForwardList< T >::clear() noexcept
  {
    deleteList(begin_);
    end_ = nullptr;
    size_ = 0;
  }

  template< typename T >
  typename ForwardList< T >::reference ForwardList< T >::front()
  {
    return begin_->data;
  }

  template< typename T >
  typename ForwardList< T >::const_reference ForwardList< T >::front() const
  {
    return begin_->data;
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, const value_type &val)
  {
    auto *newNode = new List< T >(val);
    newNode->next = pos.node_->next;
    pos.node_->next = newNode;
    if (pos.node_ == fakeNode_) {
      if (!end_) {
        end_ = begin_;
      }
      begin_ = newNode;
    } else if (!newNode->next) {
      end_ = newNode;
    }
    size_++;
    return iterator(pos.node_->next);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, value_type &&val)
  {
    return insert_after(pos, val);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, size_type n, const value_type &val)
  {
    for (size_type i = 0; i < n; ++i)
    {
      pos = insert_after(pos, val);
    }
    return iterator(pos.node_->next);
  }

  template< typename T >
  void ForwardList< T >::push_front(const value_type &val)
  {
     insert_after(cbefore_begin(), val);
  }

  template< typename T >
  void ForwardList< T >::push_front(value_type &&val)
  {
    insert_after(cbefore_begin(), std::move(val));
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::erase_after(const_iterator pos)
  {
    auto next = pos.node_->next;
    if (next) {
      pos.node_->next = next->next;
    }
    if (pos.node_ == fakeNode_) {
      begin_ = pos.node_->next;
    }
    if (next) {
      delete next;
    }
    size_--;
    if (size_ == 1) {
      end_ = nullptr;
    } else if (size_ == 0) {
      begin_ = nullptr;
      end_ = nullptr;
      fakeNode_->next = nullptr;
    }
    return iterator(pos.node_->next);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::erase_after(const_iterator pos, const_iterator last)
  {
    while (pos != last) {
      pos = erase_after(pos);
    }
    return iterator(last.node_);
  }

  template< typename T >
  void ForwardList< T >::pop_front()
  {
    erase_after(cbefore_begin());
  }

  template< typename T >
  ForwardList< T > &ForwardList< T >::operator=(const this_t &rhs)
  {
    if (std::addressof(rhs) != this) {
      clear();
      copy(rhs);
    }
    return *this;
  }

  template< typename T >
  ForwardList< T > &ForwardList< T >::operator=(this_t &&rhs)
  {
    if (std::addressof(rhs) != this) {
      clear();
      std::swap(fakeNode_, rhs.fakeNode_);
      std::swap(begin_, rhs.begin_);
      std::swap(end_, rhs.end_);
      std::swap(size_, rhs.size_);
    }
    return *this;
  }

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    clear();
    ::operator delete(fakeNode_);
  }
}
#endif
