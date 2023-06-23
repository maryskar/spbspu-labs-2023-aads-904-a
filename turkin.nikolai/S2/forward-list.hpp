#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include <cstddef>
#include <memory>
#include <cassert>
#include <initializer_list>
#include <oneway-list.hpp>
#include "iterator.hpp"
#include "const-iterator.hpp"

namespace turkin
{
  template< typename T >
  class ForwardList
  {
    public:
      using fl = ForwardList< T >;
      using it = Iterator< T >;
      using cit = ConstIterator< T >;
      ForwardList(); //done
      ForwardList(const fl & rhs); //done
      ForwardList(fl && rhs); //done
      ForwardList & operator=(const fl & rhs); //done
      ForwardList & operator=(fl && rhs); //done
      ~ForwardList(); //done
      void assign(std::size_t count, const T & value);
      T & front(); //done
      const T & front() const; //done
      it before_begin() noexcept; //done
      cit before_begin() const noexcept; //done
      cit cbefore_begin() const noexcept; // done
      it begin() noexcept; //done
      cit begin() const noexcept; //done
      cit cbegin() const noexcept; //done
      it end() noexcept; //done
      cit end() const noexcept; //done
      cit cend() const noexcept; //done
      bool empty() const noexcept; //done
      void clear() noexcept; //done
      std::size_t size() const noexcept;
      it insert_after(cit pos, const T & value); //?
      it insert_after(cit pos, T && value);
      it insert_after(cit pos, std::size_t const, const T & value);
      template< class InputIt >
      it insert_after(cit pos, InputIt firts, InputIt last);
      it insert_after(cit pos, std::initializer_list< T > ilist);
      template< class... Args >
      it emplace_after(cit pos, Args &&... args);
      it erase_after(cit pos); //
      it erase_after(cit first, cit last);
      void push_front(const T & value); //done
      void push_front(T && value); //?
      template< class... Args >
      void emplace_front(Args &&... args);
      template< class... Args >
      T & emplace_front(Args &&... args);
      void pop_front();
      void resize(std::size_t count);
      void swap(fl & other);

      void merge(fl & other);
      void merge(fl && other);
      template< class Compare >
      void merge(fl & other, Compare comp);
      template< class Compare >
      void merge(fl && other, Compare comp);
      void splice_after(cit pos, fl & other);
      void splice_after(cit pos, fl && other);
      void splice_after(cit pos, fl & other, cit it);
      void splice_after(cit pos, fl && other, cit it);
      void splice_after(cit pos, fl & other, cit first, cit last);
      void splice_after(cit pos, fl && other, cit first, cit last);
      void remove(const T & value);
      template< class UnaryPredicate >
      void remove_if(UnaryPredicate p);
      void reverse() noexcept;
      void unique();
      template< class BinaryPredicate >
      void unique(BinaryPredicate p);
      void sort();
      template< class Compare >
      void sort(Compare comp);
    private:
      it head_;
      it tail_;
      it dummy_;
      std::size_t size_;
      void copy(const fl & rhs);
  };
}

using namespace turkin;

template< typename T >
ForwardList< T >::ForwardList():
  head_(nullptr),
  tail_(nullptr),
  dummy_(new OneWayNode< T >),
  size_(0)
{
  dummy_.cur_->next = head_.cur_;
}

template< typename T >
ForwardList< T >::ForwardList(const fl & rhs):
  head_(nullptr),
  tail_(nullptr),
  dummy_(nullptr),
  size_(rhs.size_)
{
  copy(rhs);
}

template< typename T >
ForwardList< T >::ForwardList(fl && rhs):
  head_(rhs.head_),
  tail_(rhs.tail_),
  dummy_(rhs.dummy_),
  size_(rhs.size_)
{
  rhs.head_ = nullptr;
  rhs.tail_ = nullptr;
  rhs.dummy_ = nullptr;
  rhs.size_ = 0;
}

template< typename T >
ForwardList< T > & ForwardList< T >::operator=(const fl & rhs)
{
  if (std::addressof(rhs) == this)
  {
    return * this;
  }
  clear();
  copy(rhs);
  return * this;
}

template< typename T >
ForwardList< T > & ForwardList< T >::operator=(fl && rhs)
{
  if (std::addressof(rhs) == this)
  {
    return * this;
  }
  clear();
  head_ = rhs.head_;
  tail_ = rhs.tail_;
  dummy_ = rhs.dummy_;
  size_ = rhs.size_;
  rhs.head_ = nullptr;
  rhs.tail_ = nullptr;
  rhs.dummy_ = nullptr;
  rhs.size_ = nullptr;
}

template< typename T >
ForwardList< T >::~ForwardList()
{
  clear();
}

template< typename T >
T & ForwardList< T >::front()
{
  assert(head_ != nullptr);
  return head_.cur_->data;
}

template< typename T >
const T & ForwardList< T >::front() const
{
  assert(head_ != nullptr);
  return head_.cur_->data;
}

template< typename T >
Iterator< T > ForwardList< T >::before_begin() noexcept
{
  return dummy_;
};

template< typename T >
ConstIterator< T > ForwardList< T >::before_begin() const noexcept
{
  return dummy_;
};

template< typename T >
ConstIterator< T > ForwardList< T >::cbefore_begin() const noexcept
{
  return cit(dummy_);
};

template< typename T >
Iterator< T > ForwardList< T >::begin() noexcept
{
  return head_;
};

template< typename T >
ConstIterator< T > ForwardList< T >::begin() const noexcept
{
  return head_;
};

template< typename T >
ConstIterator< T > ForwardList< T >::cbegin() const noexcept
{
  return cit(head_);
};

template< typename T >
Iterator< T > ForwardList< T >::end() noexcept
{
  return tail_;
};

template< typename T >
ConstIterator< T > ForwardList< T >::end() const noexcept
{
  return tail_;
};

template< typename T >
ConstIterator< T > ForwardList< T >::cend() const noexcept
{
  return cit(tail_);
};

template< typename T >
bool ForwardList< T >::empty() const noexcept
{
  return head_.cur_ == nullptr;
};

template< typename T >
void ForwardList< T >::clear() noexcept
{
  free(dummy_.cur_);
  head_.cur_ = nullptr;
  tail_.cur_ = nullptr;
  dummy_.cur_ = nullptr;
  size_ = 0;
};

template< typename T >
std::size_t ForwardList< T >::size() const noexcept
{
  return size_;
};

template< typename T >
Iterator< T > ForwardList< T >::insert_after(cit pos, const T & value)
{
  auto * ins = new OneWayNode< T > {value, pos.cur_->next};
  if (pos.cur_ == dummy_.cur_)
  {
    pos.cur_->next = ins;
    tail_ = head_;
  }
  else
  {
    pos.cur_->next = ins;
  }
  pos++;
  size_++;
  return it(pos);
}

template< typename T >
void ForwardList< T >::push_front(const T & value)
{
  auto ins = it(new OneWayNode< T > {value, nullptr});
  if (head_.cur_)
  {
    ins.cur_->next = head_.cur_;
    if (!tail_.cur_)
    {
      tail_ = head_;
    }
    head_ = ins;
  }
  else
  {
    head_ = ins;
  }
  dummy_.cur_->next = head_.cur_;
  size_++;
}

template< typename T >
void ForwardList< T >::push_front(T && value)
{
  auto ins = it(new OneWayNode< T > {value, nullptr});
  if (head_.cur_)
  {
    ins.cur_->next = head_.cur_;
    if (!tail_.cur_)
    {
      tail_ = head_;
    }
    head_ = ins;
  }
  else
  {
    head_ = ins;
  }
  dummy_.cur_->next = head_.cur_;
  size_++;
}

template< typename T >
void ForwardList< T >::pop_front()
{
  erase_after(before_begin());
}

template< typename T >
void ForwardList< T >::copy(const fl & rhs)
{
  auto clone = copyList(rhs.head_.cur_);
  head_.cur_ = clone.first;
  tail_.cur_ = clone.second;
  dummy_.cur_->next = head_.cur_;
}

#endif
