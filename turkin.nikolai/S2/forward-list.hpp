#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include <cstddef>
#include <memory>
#include <cassert>
#include <initializer_list>
#include <oneway-list.hpp>

namespace turkin
{
  template< typename T, class Iterator, class ConstIterator>
  class ForwardList
  {
    public:
      using fl = ForwardList< T, Iterator, ConstIterator >;
      ForwardList(); //done
      ForwardList(const fl & rhs); //done
      ForwardList(fl && rhs); //done
      ForwardList & operator=(const fl & rhs); //done
      ForwardList & operator=(fl && rhs); //done
      ~ForwardList(); //done
      void assign(size_t count, const T & value);
      T & front(); //done
      const T & front() const; //done
      Iterator before_begin() noexcept; //done
      ConstIterator before_begin() const noexcept; //done
      ConstIterator cbefore_begin() const noexcept; // done
      Iterator begin() noexcept; //done
      ConstIterator begin() const noexcept; //done
      ConstIterator cbegin() const noexcept; //done
      Iterator end() noexcept; //done
      ConstIterator end() const noexcept; //done
      ConstIterator cend() const noexcept; //done
      bool empty() const noexcept; //done
      void clear() noexcept; //done
      Iterator insert_after(ConstIterator pos, const T & value); //?
      Iterator insert_after(ConstIterator pos, T && value);
      Iterator insert_after(ConstIterator pos, size_t const, const T & value);
      template< class InputIt >
      Iterator insert_after(ConstIterator pos, InputIt firts, InputIt last);
      Iterator insert_after(ConstIterator pos, std::initializer_list< T > ilist);
      template< class... Args >
      Iterator emplace_after(ConstIterator pos, Args &&... args);
      Iterator erase_after(ConstIterator pos); //
      Iterator erase_after(ConstIterator first, ConstIterator last);
      void push_front(const T & value); //done
      void push_front(T && value); //?
      template< class... Args >
      void emplace_front(Args &&... args);
      template< class... Args >
      T & emplace_front(Args &&... args);
      void pop_front();
      void resize(size_t count);
      void swap(fl & other);

      void merge(fl & other);
      void merge(fl && other);
      template< class Compare >
      void merge(fl & other, Compare comp);
      template< class Compare >
      void merge(fl && other, Compare comp);
      void splice_after(ConstIterator pos, fl & other);
      void splice_after(ConstIterator pos, fl && other);
      void splice_after(ConstIterator pos, fl & other, ConstIterator it);
      void splice_after(ConstIterator pos, fl && other, ConstIterator it);
      void splice_after(ConstIterator pos, fl & other, ConstIterator first, ConstIterator last);
      void splice_after(ConstIterator pos, fl && other, ConstIterator first, ConstIterator last);
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
      OneWayNode< T > * head_;
      OneWayNode< T > * tail_;
      OneWayNode< T > * dummy_;
      size_t size_;
      void copy(const fl & rhs);
  };
}

using namespace turkin;
//template< typename T, class Iterator, class ConstIterator>
//using fl = turkin::ForwardList< T, Iterator, ConstIterator>;

template< typename T, class Iterator, class ConstIterator >
ForwardList< T, Iterator, ConstIterator >::ForwardList():
  head_(nullptr),
  tail_(nullptr),
  dummy_(new OneWayNode< T >),
  size_(0)
{
  dummy_->next = nullptr;
}

template< typename T, class Iterator, class ConstIterator >
ForwardList< T, Iterator, ConstIterator >::ForwardList(const ForwardList< T, Iterator, ConstIterator > & rhs):
  head_(nullptr),
  tail_(nullptr),
  dummy_(nullptr),
  size_(rhs.size_)
{
  copy(rhs);
}

template< typename T, class Iterator, class ConstIterator >
ForwardList< T, Iterator, ConstIterator >::ForwardList(ForwardList< T, Iterator, ConstIterator > && rhs):
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

template< typename T, class Iterator, class ConstIterator >
ForwardList< T, Iterator, ConstIterator> & ForwardList< T, Iterator, ConstIterator >::operator=(const ForwardList< T, Iterator, ConstIterator > & rhs)
{
  if (std::addressof(rhs) == this)
  {
    return * this;
  }
  clear();
  copy(rhs);
  return * this;
}

template< typename T, class Iterator, class ConstIterator >
ForwardList< T, Iterator, ConstIterator> & ForwardList< T, Iterator, ConstIterator >::operator=(ForwardList< T, Iterator, ConstIterator > && rhs)
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

template< typename T, class Iterator, class ConstIterator >
ForwardList< T, Iterator, ConstIterator >::~ForwardList()
{
  clear();
}

template< typename T, class Iterator, class ConstIterator >
T & ForwardList< T, Iterator, ConstIterator >::front()
{
  assert(head_ != nullptr);
  return head_->data;
}

template< typename T, class Iterator, class ConstIterator >
const T & ForwardList< T, Iterator, ConstIterator >::front() const
{
  assert(head_ != nullptr);
  return head_->data;
}

template< typename T, class Iterator, class ConstIterator >
Iterator ForwardList< T, Iterator, ConstIterator >::before_begin() noexcept
{
  return Iterator(dummy_);
};

template< typename T, class Iterator, class ConstIterator >
ConstIterator ForwardList< T, Iterator, ConstIterator >::before_begin() const noexcept
{
  return ConstIterator(dummy_);
};

template< typename T, class Iterator, class ConstIterator >
ConstIterator ForwardList< T, Iterator, ConstIterator >::cbefore_begin() const noexcept
{
  return ConstIterator(dummy_);
};

template< typename T, class Iterator, class ConstIterator >
Iterator ForwardList< T, Iterator, ConstIterator >::begin() noexcept
{
  return Iterator(head_);
};

template< typename T, class Iterator, class ConstIterator >
ConstIterator ForwardList< T, Iterator, ConstIterator >::begin() const noexcept
{
  return ConstIterator(head_);
};

template< typename T, class Iterator, class ConstIterator >
ConstIterator ForwardList< T, Iterator, ConstIterator >::cbegin() const noexcept
{
  return ConstIterator(head_);
};

template< typename T, class Iterator, class ConstIterator >
Iterator ForwardList< T, Iterator, ConstIterator >::end() noexcept
{
  return Iterator(tail_);
};

template< typename T, class Iterator, class ConstIterator >
ConstIterator ForwardList< T, Iterator, ConstIterator >::end() const noexcept
{
  return ConstIterator(tail_);
};

template< typename T, class Iterator, class ConstIterator >
ConstIterator ForwardList< T, Iterator, ConstIterator >::cend() const noexcept
{
  return ConstIterator(tail_);
};

template< typename T, class Iterator, class ConstIterator >
bool ForwardList< T, Iterator, ConstIterator >::empty() const noexcept
{
  return head_ == nullptr;
};

template< typename T, class Iterator, class ConstIterator >
void ForwardList< T, Iterator, ConstIterator >::clear() noexcept
{
  free(head_);
  delete dummy_;
  head_ = nullptr;
  tail_ = nullptr;
  dummy_ = nullptr;
  size_ = 0;
};

template< typename T, class Iterator, class ConstIterator >
Iterator ForwardList< T, Iterator, ConstIterator >::insert_after(ConstIterator pos, const T & value)
{
  auto * ins = OneWayNode< T > {value, nullptr};
  ins->next = pos.cur_->next;
  pos.cur_->next = ins;
  if (pos.cur_ == dummy_)
  {
    if (tail_ == nullptr)
    {
      tail_ = head_;
    }
    head_ = ins;
  }
  else if (ins->next == nullptr)
  {
    tail_ = ins;
  }
  size_++;
  return Iterator(pos.cur_->next);
}

template< typename T, class Iterator, class ConstIterator >
Iterator ForwardList< T, Iterator, ConstIterator >::erase_after(ConstIterator pos)
{
  ConstIterator npos(pos);
  npos++;
  auto ins = npos;
  if (ins)
  {
    pos.cur_->next = ins->next;
  }
  if (pos.cur_ == dummy_)
  {
    head_ = pos.cur_->next;
  }
  if (ins)
  {
    delete ins;
  }
  size_--;
  if (size_ == 1)
  {
    tail_ = nullptr;
  }
  else if (size_ == 0)
  {
    head_ = nullptr;
    tail_ = nullptr;
    dummy_->next = nullptr;
  }
  return iterator(pos.cur_->next);
}

template< typename T, class Iterator, class ConstIterator >
Iterator ForwardList< T, Iterator, ConstIterator >::erase_after(ConstIterator first, ConstIterator last)
{
  auto head = first;
  while (first != last)
  {
    first = erase_after(head);
  }
  return Iterator(last);
}

template< typename T, class Iterator, class ConstIterator >
void ForwardList< T, Iterator, ConstIterator >::push_front(const T & value)
{
  auto * ins = new OneWayNode< T > {value, nullptr};
  if (head_)
  {
    ins->next = head_;
    if (!tail_)
    {
      tail_ = head_;
    }
    head_ = ins;
  }
  else
  {
    head_ = ins;
  }
  dummy_->next = head_;
  size_++;
}

template< typename T, class Iterator, class ConstIterator >
void ForwardList< T, Iterator, ConstIterator >::push_front(T && value)
{
  auto * ins = new OneWayNode< T > {value, nullptr};
  if (head_)
  {
    ins->next = head_;
    if (!tail_)
    {
      tail_ = head_;
    }
    head_ = ins;
  }
  else
  {
    head_ = ins;
  }
  dummy_->next = head_;
  size_++;
}

template< typename T, class Iterator, class ConstIterator >
void ForwardList< T, Iterator, ConstIterator >::pop_front()
{
  erase_after(before_begin());
}

template< typename T, class Iterator, class ConstIterator >
void ForwardList< T, Iterator, ConstIterator >::copy(const ForwardList< T, Iterator, ConstIterator > & rhs)
{
  auto clone = copyList(rhs.head_);
  head_ = clone.first;
  tail_ = clone.second;
  dummy_->next = head_;
}

#endif
