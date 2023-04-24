#ifndef S2_FORWARD_LIST_HPP
#define S2_FORWARD_LIST_HPP
#include <initializer_list>
#include <iterator>
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
    *(rhs.begin()) = nullptr;
    if (!empty())
    {
      last_.node_->next = fake_;
    }
  }

  template< typename T >
  ForwardList< T >::ForwardList(std::initializer_list< T > init)//.......
  {
  }

  template< typename T >
  template< typename InputIt >
  ForwardList< T >::ForwardList(InputIt first, InputIt last):
   ForwardList()
  {
    fake_.node_->next = first;
    //
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
    *this = std::move(temp);
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
    buf_ = rhs.buf_;
    fake_ = std::addressof(buf_);
    last_ = rhs.last_;
    *(rhs.begin()) = nullptr;
    if (!empty())
    {
      last_.node_->next = fake_;
    }
    return *this;
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, const_reference value)
  {
    pos.node_->next = new detail::List< T >{value, pos.node_->next};
    return ++pos;
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert_after(ForwardList::const_iterator pos, T && value)
  {
    pos.node_->next = new detail::List< T >{std::move(value), pos.node_->next};
    return ++pos;
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, size_type count, const_reference value)
  {
    for (size_type i = 0; i < count; ++i)
    {
      pos = insert_after(pos, value);
    }
    return pos;
  }

  template< typename T >
  template< typename InputIt >
  typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, InputIt first, InputIt last)
  {
    for (first; first != last_; ++first)
    {
      pos = insert_after(pos, *first);
    }
    return pos;
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
    return ++pos;
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::erase_after(const_iterator pos)
  {
    detail::List< T > * temp = pos.node_->next->next;
    delete pos.node_->next;
    pos.node_->next = temp;
    return iterator(temp);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::erase_after(const_iterator first, const_iterator last)
  {
    while (first != last)
    {
      erase_after(first);
    }
    return last;
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
    detail::List< T > * temp = cbegin().node_->next;
    delete begin().node_;
    fake_.node_->next = temp;
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
