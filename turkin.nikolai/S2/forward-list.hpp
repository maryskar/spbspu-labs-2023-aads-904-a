#include <cstddef>
#include <memory>
#include <initializer_list>
#include <oneway-list.hpp>

namespace turkin
{
  template< typename T, class Iterator, class ConstIterator>
  class ForwardList
  {
    public:
      using fl = ForwardList< T, Iterator, ConstIterator >;
      ForwardList();
      ForwardList(const fl & rhs);
      ForwardList(fl && rhs);
      ForwardList & operator=(const fl & rhs);
      ForwardList & operator=(fl && rhs);
      ~ForwardList();
      void assign(size_t count, const T & value);
      T & front();
      const T & front() const;
      Iterator before_begin() noexcept;
      ConstIterator before_begin() const noexcept;
      ConstIterator cbefore_begin() const noexcept;
      Iterator begin() noexcept;
      ConstIterator begin() const noexcept;
      ConstIterator cbegin() const noexcept;
      Iterator end() noexcept;
      ConstIterator end() const noexcept;
      ConstIterator cend() const noexcept;
      bool empty() const noexcept;
      size_t max_size() const noexcept;
      void clear() noexcept;
      Iterator insert_after(ConstIterator pos, const T & value);
      Iterator insert_after(ConstIterator pos, T && value);
      Iterator insert_after(ConstIterator pos, size_t const, const T & value);
      template< class InputIt >
      Iterator insert_after(ConstIterator pos, InputIt firts, InputIt last);
      Iterator insert_after(ConstIterator pos, std::initializer_list< T > ilist);
      template< class... Args >
      Iterator emplace_after(ConstIterator pos, Args &&... args);
      Iterator erase_after(ConstIterator pos);
      Iterator erase_after(ConstIterator first, ConstIterator last);
      void push_front(const T & value);
      void push_front(T && value);
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
template< typename T, class Iterator, class ConstIterator>
using fl = ForwardList< T, Iterator, ConstIterator>;

template< typename T, class Iterator, class ConstIterator >
fl< T, Iterator, ConstIterator >::ForwardList():
  head_(nullptr),
  tail_(nullptr),
  dummy_(new OneWayNode< T >),
  size_(0)
{
  dummy_->next = nullptr;
}

template< typename T, class Iterator, class ConstIterator >
fl< T, Iterator, ConstIterator >::ForwardList(const fl & rhs):
  head_(nullptr),
  tail_(nullptr),
  dummy_(nullptr),
  size_(rhs.size_)
{
  copy(rhs);
}

template< typename T, class Iterator, class ConstIterator >
fl< T, Iterator, ConstIterator >::ForwardList(fl && rhs):
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
fl< T, Iterator, ConstIterator> & fl< T, Iterator, ConstIterator >::operator=(const fl & rhs)
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
fl< T, Iterator, ConstIterator> & fl< T, Iterator, ConstIterator >::operator=(fl && rhs)
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
fl< T, Iterator, ConstIterator >::~ForwardList()
{
  free(head_);
}

template< typename T, class Iterator, class ConstIterator >
void fl< T, Iterator, ConstIterator >::copy(const fl & rhs)
{
  auto clone = copyList(rhs.head_);
  head_ = clone.first;
  tail_ = clone.second;
  dummy_->next = head_;
}
