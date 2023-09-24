#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <iosfwd>
#include <stdexcept>
#include "iterator.h"
#include "citerator.h"
#include "list.h"

namespace skarlygina
{
  template < typename T >
  class ForwardList
  {
  public:
    ForwardList();
    ForwardList(const ForwardList< T >&);
    ForwardList(ForwardList< T >&&) noexcept;
    ~ForwardList();

    Iterator< T > begin();
    Iterator< T > end();
    CIterator< T > begin() const;
    CIterator< T > end() const;
    CIterator< T > cbegin() const;
    CIterator< T > cend() const;

    bool isEmpty() const noexcept;
    size_t getSize() const;
    T front() const;
    T back() const;
    void clear();
    Iterator< T > insertAfter(CIterator< T >, const T&);
    Iterator< T > eraseAfter(CIterator< T >);
    void pushBack(const T&);
    void pushFront(const T&);
    void popFront();
    void popBack();

  private:
    List< T >* head_;
    List< T >* tail_;
    size_t size_;

  };

  template < typename T >
  bool ForwardList< T >::isEmpty() const noexcept
  {
    return !size_;
  }

  template < typename T >
  size_t ForwardList< T >::getSize() const
  {
    return size_;
  }

  template < typename T >
  T ForwardList< T >::front() const
  {
    if (!size_)
    {
      throw std::logic_error("List is empty");
    }
    return head_->data;
  }

  template < typename T >
  T ForwardList< T >::back() const
  {
    if (!size_)
    {
      throw std::logic_error("List is empty");
    }
    return tail_->data;
  }

  template< typename T >
  void ForwardList< T >::clear()
  {
    while (head_)
    {
      auto temp = head_;
      head_ = head_->next;
      delete temp;
      --size_;
    }
  }

  template< typename T >
  Iterator< T > ForwardList< T >::insertAfter(CIterator< T > pos, const T& data_)
  {
    auto pos_ptr = const_cast< List< T >* >(pos.ptr_);
    if (!pos_ptr->next)
    {
      pushBack(data_);
      return Iterator< T >(++pos);
    }
    auto temp = pos_ptr->next;
    pos_ptr->next = new List< T >{data_, temp};
    temp = nullptr;
    ++size_;
    return Iterator< T >(++pos);
  }

  template< typename T >
  Iterator< T > ForwardList< T >::eraseAfter(CIterator< T > pos)
  {
    auto pos_ptr = const_cast< List< T >* >(pos.ptr_);
    if (pos_ptr->next == tail_)
    {
      popBack();
      return end();
    }
    auto temp = pos_ptr->next->next;
    delete pos_ptr->next;
    pos_ptr->next = temp;
    --size_;
    return Iterator< T >(++pos);
  }

  template < typename T >
  void ForwardList< T >::pushBack(const T& data_)
  {
    if (!size_)
    {
      head_ = new List< T >{data_, nullptr};
      tail_ = head_;
    }
    else
    {
      tail_->next = new List< T >{data_, nullptr};
      tail_ = tail_->next;
    }
    ++size_;
  }

  template < typename T >
  void ForwardList< T >::pushFront(const T& data_)
  {
    if (!size_)
    {
      head_ = new List< T >{data_, nullptr};
      tail_ = head_;
    }
    else
    {
      auto new_head = new List< T >{data_, head_};
      head_ = new_head;
    }
    ++size_;
  }

  template < typename T >
  void ForwardList< T >::popFront()
  {
    if (!size_)
    {
      throw std::logic_error("Pop from the empty list");
    }
    auto temp(head_);
    head_ = head_->next;
    delete temp;
    --size_;
  }

  template < typename T >
  void ForwardList< T >::popBack()
  {
    if (!size_)
    {
      throw std::logic_error("Pop from empty list");
    }
    if (size_ == 1)
    {
      popFront();
      return;
    }
    auto current = head_;
    while (current->next->next)
    {
      current = current->next;
    }
    delete current->next;
    current->next = nullptr;
    tail_ = current;
    --size_;
  }

  template< typename T >
  ForwardList< T >::ForwardList():
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template< typename T >
  ForwardList< T >::ForwardList(const ForwardList< T >& other):
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {
    if (!other.isEmpty())
    {
      try
      {
        List< T >* other_ptr = other.head_;
        do
        {
          pushBack(other_ptr->data);
          other_ptr = other_ptr->next;
        } while (other_ptr);
      }
      catch (...)
      {
        clear();
        throw;
      }
    }
  }

  template< typename T >
  ForwardList< T >::ForwardList(ForwardList< T >&& other) noexcept:
    head_(other.head_),
    tail_(other.tail_),
    size_(other.size_)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
  }

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    clear();
  }

  template < typename T >
  Iterator< T > ForwardList< T >::begin()
  {
    return Iterator< T >(cbegin());
  }

  template < typename T >
  Iterator< T > ForwardList< T >::end()
  {
    return Iterator< T >(cend());
  }

  template < typename T >
  CIterator< T > ForwardList< T >::begin() const
  {
    return CIterator< T >(cbegin());
  }
  template < typename T >
  CIterator< T > ForwardList< T >::end() const
  {
    return CIterator< T >(cend());
  }

  template < typename T >
  CIterator< T > ForwardList< T >::cbegin() const
  {
    return CIterator< T >(head_);
  }
  template < typename T >
  CIterator< T > ForwardList< T >::cend() const
  {
    return CIterator< T >(nullptr);
  }
}
#endif
