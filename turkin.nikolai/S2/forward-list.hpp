#include <cstddef>
#include <initializer_list>
#include <oneway-list.hpp>

namespace turkin
{
  template< typename T, class Iterator, class ConstIterator>
  class ForwardList
  {
    public:
      ForwardList();
      ForwardList(const ForwardList< T, Iterator, ConstIterator > & rhs);
      ForwardList(ForwardList< T, Iterator, ConstIterator > && rhs);
      ForwardList & operator=(const ForwardList< T, Iterator, ConstIterator > & rhs);
      ForwardList & operator=(ForwardList< T, Iterator, ConstIterator > && rhs);
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
      void swap(ForwardList< T, Iterator, ConstIterator > & other);

      void merge(ForwardList< T, Iterator, ConstIterator > & other);
      void merge(ForwardList< T, Iterator, ConstIterator > && other);
      template< class Compare >
      void merge(ForwardList< T, Iterator, ConstIterator > & other, Compare comp);
      template< class Compare >
      void merge(ForwardList< T, Iterator, ConstIterator > && other, Compare comp);
      void splice_after(ConstIterator pos, ForwardList< T, Iterator, ConstIterator > & other);
      void splice_after(ConstIterator pos, ForwardList< T, Iterator, ConstIterator > && other);
      void splice_after(ConstIterator pos, ForwardList< T, Iterator, ConstIterator > & other, ConstIterator it);
      void splice_after(ConstIterator pos, ForwardList< T, Iterator, ConstIterator > && other, ConstIterator it);
      void splice_after(ConstIterator pos, ForwardList< T, Iterator, ConstIterator > & other, ConstIterator first, ConstIterator last);
      void splice_after(ConstIterator pos, ForwardList< T, Iterator, ConstIterator > && other, ConstIterator first, ConstIterator last);
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
  };
}

template< typename T, class Iterator, class ConstIterator >
turkin::ForwardList< T, Iterator, ConstIterator >::ForwardList():
  head_(nullptr),
  tail_(nullptr),
  dummy_(nullptr)
{}
