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
      std::size_t size() const noexcept; //done

      it insert_after(cit pos, const T & value); //done
      it insert_after(cit pos, T && value);
      it insert_after(cit pos, std::size_t const, const T & value);
      template< class InputIt >
      it insert_after(cit pos, InputIt firts, InputIt last);
      it insert_after(cit pos, std::initializer_list< T > ilist);

      template< class... Args >
      it emplace_after(cit pos, Args &&... args); //done
      it erase_after(cit pos); //done
      it erase_after(cit first, cit last); //done

      void push_front(const T & value); //done
      template< class... Args >
      void emplace_front(Args &&... args);
      template< class... Args >
      T & emplace_front(Args &&... args);
      void pop_front();
      void swap(fl & other) noexcept; //done

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
      it dummy_;
      it tail_;
      std::size_t size_;
      void copy(const fl & rhs);
  };
}

using namespace turkin;

template< typename T >
ForwardList< T >::ForwardList():
  dummy_(new OneWayNode< T >),
  tail_(it(nullptr)),
  size_(0)
{
  dummy_.cur_->next = tail_.cur_;
}

template< typename T >
ForwardList< T >::ForwardList(const fl & rhs):
  dummy_(it(nullptr)),
  tail_(it(nullptr)),
  size_(rhs.size_)
{
  copy(rhs);
}

template< typename T >
ForwardList< T >::ForwardList(fl && rhs):
  dummy_(rhs.dummy_),
  tail_(rhs.tail_),
  size_(rhs.size_)
{
  rhs.tail_ = it(nullptr);
  rhs.dummy_ = it(nullptr);
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
  tail_ = rhs.tail_;
  dummy_ = rhs.dummy_;
  size_ = rhs.size_;
  rhs.head_ = it(nullptr);
  rhs.tail_ = it(nullptr);
  rhs.dummy_ = it(nullptr);
  rhs.size_ = 0;
}

template< typename T >
ForwardList< T >::~ForwardList()
{
  free(dummy_.cur_);
}

template< typename T >
T & ForwardList< T >::front()
{
  assert(dummy_.cur_->next != nullptr);
  return dummy_.cur_->next->data;
}

template< typename T >
const T & ForwardList< T >::front() const
{
  assert(dummy_.cur_->next != nullptr);
  return dummy_.cur_->next->data;
}

template< typename T >
Iterator< T > ForwardList< T >::before_begin() noexcept
{
  return dummy_;
};

template< typename T >
ConstIterator< T > ForwardList< T >::before_begin() const noexcept
{
  return cbefore_begin();
};

template< typename T >
ConstIterator< T > ForwardList< T >::cbefore_begin() const noexcept
{
  return cit(dummy_);
};

template< typename T >
Iterator< T > ForwardList< T >::begin() noexcept
{
  return it(dummy_.cur_->next);
};

template< typename T >
ConstIterator< T > ForwardList< T >::begin() const noexcept
{
  return cbegin();
};

template< typename T >
ConstIterator< T > ForwardList< T >::cbegin() const noexcept
{
  return cit(dummy_.cur_->next);
};

template< typename T >
Iterator< T > ForwardList< T >::end() noexcept
{
  return tail_;
};

template< typename T >
ConstIterator< T > ForwardList< T >::end() const noexcept
{
  return cend();
};

template< typename T >
ConstIterator< T > ForwardList< T >::cend() const noexcept
{
  return cit(tail_);
};

template< typename T >
bool ForwardList< T >::empty() const noexcept
{
  return dummy_.cur_->next == nullptr;
};

template< typename T >
void ForwardList< T >::clear() noexcept
{
  free(dummy_.cur_);
  dummy_ = it(new OneWayNode< T >);
  tail_ = it(nullptr);
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
  auto tins = it(new OneWayNode< T > {value, nullptr});
  tins.cur_->next = pos.cur_->next;
  pos.cur_->next = tins.cur_;
  size_++;
  return tins;
}

template< typename T >
template< class... Args >
Iterator< T > ForwardList< T >::emplace_after(cit pos, Args &&... args)
{
  return insert_after(pos, std::forward< T >(T(args...)));
}

template< typename T >
Iterator< T > ForwardList< T >::erase_after(cit pos)
{
  auto * ins = pos.cur_->next;
  if (ins == nullptr)
  {
    return it(pos.cur_);
  }
  pos.cur_->next = ins->next;
  delete ins;
  size_--;
  return it(pos.cur_->next);
}

template< typename T >
Iterator< T > ForwardList< T >::erase_after(cit first, cit last)
{
  for (auto ins = first; ins != last; ins++)
  {
    erase_after(ins);
  }
  return it(last.cur_->next);
}

template< typename T >
void ForwardList< T >::push_front(const T & value)
{
  if (dummy_.cur_->next == nullptr)
  {
    dummy_.cur_->next = new OneWayNode< T > {value, nullptr};
    tail_.cur_ = dummy_.cur_->next;
  }
  else
  {
    dummy_.cur_->next = new OneWayNode< T > {value, dummy_.cur_->next};
  }
  size_++;
}

template< typename T >
void ForwardList< T >::pop_front()
{
  auto temp = dummy_.cur_->next;
  dummy_.cur_->next = temp->next;
  delete temp;
}

template< typename T >
void ForwardList< T >::swap(fl & other) noexcept
{
  std::swap(dummy_, other.dummy_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template< typename T >
void ForwardList< T >::copy(const fl & rhs)
{
  auto clone = copyList(rhs.dummy_.cur_);
  dummy_.cur_ = clone.first;
  tail_.cur_ = clone.second;
}

#endif
