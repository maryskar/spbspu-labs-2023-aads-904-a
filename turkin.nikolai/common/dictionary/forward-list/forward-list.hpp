#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include <cstddef>
#include <memory>
#include <cassert>
#include <initializer_list>
#include "oneway-list.hpp"
#include "iterators/iterator.hpp"
#include "iterators/const-iterator.hpp"

namespace turkin
{
  template< typename T >
  class ForwardList
  {
    using fl = ForwardList< T >;
    using it = Iterator< T >;
    using cit = ConstIterator< T >;
    public:
      ForwardList();
      ForwardList(const fl & rhs);
      ForwardList(fl && rhs);
      ForwardList(std::initializer_list< T > & list);
      ForwardList & operator=(const fl & rhs);
      ForwardList & operator=(fl && rhs);
      ~ForwardList();
      T & front();
      const T & front() const;
      it before_begin() noexcept;
      cit before_begin() const noexcept;
      cit cbefore_begin() const noexcept;
      it begin() noexcept;
      cit begin() const noexcept;
      cit cbegin() const noexcept;
      it end() noexcept;
      cit end() const noexcept;
      cit cend() const noexcept;
      bool empty() const noexcept;
      void clear() noexcept;
      std::size_t size() const noexcept;

      it insert_after(cit pos, const T & value);

      template< class... Args >
      it emplace_after(cit pos, Args &&... args);
      it erase_after(cit pos);
      it erase_after(cit first, cit last);

      void push_front(const T & value);
      void pop_front();
      void swap(fl & other) noexcept;

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
  tail_(new OneWayNode< T >),
  size_(0)
{
  dummy_.cur_->next = tail_.cur_;
  tail_.cur_->next = nullptr;
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
ForwardList< T >::ForwardList(std::initializer_list< T > & list):
  dummy_(static_cast< OneWayNode< T > * >(::operator new (sizeof(OneWayNode< T >)))),
  tail_(static_cast< OneWayNode< T > * >(::operator new (sizeof(OneWayNode< T >)))),
  size_(0)
{
  dummy_.cur_->next = tail_.cur_;
  tail_.cur_->next = nullptr;
  for (auto ins: list)
  {
    insert_after(cend(), ins);
  }
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
  rhs.tail_ = it(nullptr);
  rhs.dummy_ = it(nullptr);
  rhs.size_ = 0;
  return * this;
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
  return size_ == 0;
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
