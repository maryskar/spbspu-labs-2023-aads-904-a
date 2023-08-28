#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <cstddef>
#include <stdexcept>
#include "ForwardListIter.h"
#include "ForwardListConstIter.h"
#include "../common/List.h"
namespace timofeev
{
  template< typename T>
  class ForwardList
  {
  public:
    using iter = ForwardListIterator< T >;
    using constIter = ForwardListConstIterator< T >;

    ForwardList();
    ~ForwardList();

    ForwardList(const ForwardList< T > &lhs);  //
    ForwardList(ForwardList< T > &&rhs) noexcept;
    ForwardList< T > &operator=(const ForwardList< T > &rhs);
    ForwardList< T > &operator=(ForwardList< T > &&rhs);

    bool empty() const;  //
    void clear();  //

    iter before_begin() noexcept;
    iter begin() noexcept;
    iter end() noexcept;

    constIter cbegin() const noexcept;
    constIter cend() const noexcept;
    constIter cbefore_begin() const noexcept;

    iter insert_after(constIter pos, const T &value);
    iter insert_after(constIter pos, T &&value );
    iter insert_after(constIter pos, size_t count, const T &value );
    iter insert_after(constIter pos, iter first, iter last );
    //iter insert_after( const_iterator pos, std::initializer_list<T> ilist );

    iter erase_after(constIter pos);
    iter erase_after(constIter first, constIter last);

    template< typename ...Args >
    iter emplace_after(constIter pos, Args &&...args);
    template< typename ...Args >
    void emplace_front(Args &&...args);

    void push_front(const T &value);
    void push_front(T &&value);
    void pop_front();

    void resize(size_t count);
    void resize(size_t count, const T& value);
    void swap(ForwardList< T >& other);
    void splice_after(constIter pos, ForwardList< T > &other);
    void splice_after(constIter pos, ForwardList< T > &&other);

    void remove(const T& value);
    void remove_if(T p);

    size_t size() const noexcept;

  private:
    List< T > *head_;
    size_t size_;
  };

  template< typename T>
  ForwardList< T >::ForwardList(ForwardList< T > &&rhs) noexcept:
    head_(rhs.head_),
    size_(rhs.size_)
  {}

  template< typename T>
  ForwardList< T >::ForwardList():
    head_(nullptr),
    size_(0)
  {}

    template< typename T >
    void ForwardList< T >::clear()
    {
        List< T > *node = head_;
        while(node != nullptr)
        {
            List< T > *tmp = node->next;
            delete node;
            node = tmp;
        }
        size_ = 0;
    }

    template< typename T >
    ForwardList< T >::~ForwardList()
    {
        clear();
        ::operator delete(head_);
    }

    template< typename T >
    size_t ForwardList< T >::size() const noexcept
    {
        return size;
    }
/*void push_front(const T &value);
        void push_front(T &&value);
        void pop_front();*/
    template< typename T>
    void ForwardList< T >::push_front(const T &value)
    {
        List< T > *node = new List< T >();
        node->data = value;
        node->next = head_;
        head_ = node;
        size_++;
    }

    template< typename T >
    void ForwardList< T >::push_front(T &&value)
    {
        push_front(value);
    }

    template< typename T >
    void ForwardList< T >::pop_front()
    {
        if (!head_)
        {
          throw std::out_of_range("out of range");
        }
        List< T > *tmp = head_->next;
        delete head_;
        head_ = tmp;
        size_--;
    }

    template< typename T >
    bool ForwardList< T >::empty() const
    {
        return head_ == nullptr;
    }
/* iter insert_after(constIter pos, const T &value);
        iter insert_after(constIter pos, T &&value );
        iter insert_after(constIter pos, size_t count, const T &value );
        iter insert_after(constIter pos, iter first, iter last );
        iter insert_after( constIter pos, std::initializer_list<T> ilist )
        */
    template< typename T >
    ForwardList< T >::iter ForwardList<T>::insert_after(constIter pos, const T &value)
    {
        List< T > *node = new List< T >();
        node->data = value;
        node->next = pos->next;
        pos->next = node;
        size_++;
        return pos->next;
    }

    template< typename  T >
    ForwardList< T >::iter ForwardList<T>::insert_after(constIter pos, T &&value )
    {
        return insert_after(pos, value);
    }

    template< typename  T >
    ForwardList< T >::iter ForwardList<T>::insert_after(constIter pos, size_t count, const T &value )
    {
        for (size_t i = 0; i < count; i++)
        {
            pos = insert_after(pos, value);
            pos++;
        }
        return pos;
    }

    template< typename  T >
    ForwardList< T >::iter ForwardList<T>::insert_after(constIter pos, iter first, iter last )
    {
        while (first != last)
        {
            pos = insert_after(pos, *first);
            pos++;
            first++;
        }
        return pos;
    }
/*        iter erase_after(constIter pos);
        iter erase_after(constIter first, constIter last);*/

    template< typename  T >
    ForwardList< T >::iter ForwardList<T>::erase_after(constIter pos)
    {
        //чек проверку
        if (pos->next = nullptr)
        {
            return nullptr;
        }
        List< T > *tmp = pos;
        tmp++;
        List< T > *tmp_next = tmp->next;
        delete tmp;
        pos->next = tmp_next;
        return pos;
    }

    template< typename  T >
    ForwardList< T >::iter ForwardList<T>::erase_after(constIter first, constIter last)
    {
        //вопрос сработает ли!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        size_t count = last - first;
        for (size_t i = 0; i < count; i++)
        {
            erase_after(first);
        }
        return last;
    }

    template< typename T >
    ForwardList< T >::ForwardList(const ForwardList< T > &lhs):
      ForwardList()
    {
      if (lhs.empty())
      {
        return;
      }
      insert_after(before_begin(), lhs.cbegin(), lhs.cend());
    }


  template< typename T >
  ForwardList< T >& ForwardList< T >::operator=(ForwardList< T >&& rhs)
  {
    insert_after(before_begin(), rhs.begin(), rhs.end());
    return *this;
  }

  template< typename T >
  ForwardList< T >& ForwardList< T >::operator=(const ForwardList< T >& rhs)
  {
    *this = std::move(rhs);
    return *this;
  }

 /* iter before_begin() noexcept;
  iter begin() noexcept;
  iter end() noexcept;*/

  template< typename T >
  ForwardListIterator< T > ForwardList< T >::before_begin() noexcept
  {
    return iter(head_);
  }

  template< typename T >
  ForwardListIterator< T > ForwardList< T >::begin() noexcept
  {
    return before_begin();
  }

  template< typename T >
  ForwardListIterator< T > ForwardList< T >::end() noexcept
  {
    return iter(nullptr);
  }
  /*
  constIter cbegin() const noexcept;
  constIter cend() const noexcept;
  constIter cbefore_begin() const noexcept;*/
  template< typename T >
  ForwardListConstIterator< T > ForwardList< T >::cbegin() const noexcept
  {
    return begin();
  }

  template< typename T >
  ForwardListConstIterator< T > ForwardList< T >::cbefore_begin() const noexcept
  {
    return before_begin();
  }

  template< typename T >
  ForwardListConstIterator< T > ForwardList< T >::cend() const noexcept
  {
    return end();
  }

  template< typename T >
  void ForwardList< T >::resize(size_t count, const T& value)
  {
    size_t cur = size();
    if (count == cur )
    {
      return;
    }
    else if (cur > count)
    {
      auto erase = cbegin();
      size_t tmp = cur;
      while (tmp != count )
      {
        erase++;
        tmp--;
      }
      erase_after(erase, cend());
    }
    else
    {
      auto insert = cbegin();
      size_t tmp = cur;
      while (tmp != count )
      {
        insert++;
        tmp--;
      }
      insert_after(insert, count - cur, value);
    }
  }

  template< typename T >
  void ForwardList< T >::resize(size_t count)
  {
    resize(count, T());
  }

  template< typename T >
  void ForwardList< T >::swap(ForwardList< T >& other)
  {
    std::swap(head_, other.head_);
  }
}
#endif
