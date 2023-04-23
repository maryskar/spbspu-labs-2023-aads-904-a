#ifndef S2_FORWARD_LIST_HPP
#define S2_FORWARD_LIST_HPP
#include <initializer_list>
#include <iterator>
#include "const-forward-iterator.hpp"

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
    size_type max_size() const noexcept;
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
    void swap(this_t & other);
    void merge(this_t & other);
    void merge (this_t && other);
    template< typename Comp >
    void merge(this_t & other, Comp comp);
    template< typename Comp >
    void merge(this_t && other, Comp comp);
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
    char buf_[sizeof(detail::List< T >)];
    iterator fake_;
    iterator last_;
  };

  template< typename T >
  ForwardList< T >::ForwardList():
   fake_(new (buf_) detail::List< T >),
   last_(nullptr)
  {
    fake_.node_->next = nullptr;
  }

  template< typename T >
  bool ForwardList< T >::empty() const noexcept
  {
    return fake_.node_->next == nullptr;
  }

  template< typename T >
  void ForwardList< T >::clear() noexcept
  {
    detail::deleteList(fake_.node_->next);
  }

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    clear();
  }

  template< typename T >
  ForwardList< T >::ForwardList(const this_t & rhs):
   ForwardList()
  {
    if (rhs.empty())
    {
      return;
    }
    std::pair< detail::List< T > *, detail::List< T > * > temp = detail::copyList(rhs.fake_.node_->next);
    fake_.node_->next = temp.first;
    last_ = temp.second;
    last_.node_->next = fake_;
  }

  template< typename T >
  ForwardList< T >::ForwardList(this_t && rhs):
   buf_(rhs.buf_),
   fake_(std::addressof(buf_)),
   last_(rhs.last_)
  {
    rhs.fake_.node_->next = nullptr;
    if (!empty())
    {
      last_.node_->next = fake_;
    }
  }

  template< typename T >
  bool operator==(const ForwardList< T > & lhs, const ForwardList< T > & rhs);

  template< typename T >
  bool operator!=(const ForwardList< T > & lhs, const ForwardList< T > & rhs);
}

#endif
