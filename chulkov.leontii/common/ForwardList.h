#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <algorithm>
#include <stdexcept>
#include "ForwardConstIter.h"
#include "ForwardIter.h"

namespace chulkov {
  template < typename T >
  class ForwardIter;
  template < typename T >
  class ForwardConstIter;

  template < typename T >
  class ForwardList
  {
  public:
    ForwardList();
    ForwardList(const ForwardList& other);
    ForwardList(ForwardList&& other) noexcept;
    ~ForwardList();
    void clear();

    void swap(ForwardList& other) noexcept;
    void pushFront(const T& item);
    void popFront();
    void popAfter(ForwardIter< T >& iter);
    void pushBack(const T& item);
    void pushAfter(const ForwardConstIter< T >& iter, const T& item);
    bool isEmpty() const;
    T& front();
    const T& front() const;

    ForwardList< T >& operator=(const ForwardList< T >& other);
    ForwardList< T >& operator=(ForwardList< T >&& other);

    ForwardIter< T > insertAfter(ForwardConstIter< T >, const T&);
    ForwardIter< T > eraseAfter(ForwardConstIter< T > it);
    ForwardIter< T > begin() const noexcept;
    ForwardIter< T > end() const noexcept;
    ForwardConstIter< T > cbegin() const noexcept;
    ForwardConstIter< T > cend() const noexcept;

  private:
    List< T >* head_;
    List< T >* tail_;
  };

  template < typename T >
  ForwardList< T >::ForwardList():
    head_(nullptr),
    tail_(nullptr)
  {}

  template < typename T >
  ForwardList< T >::ForwardList(const ForwardList< T >& other):
    head_(nullptr),
    tail_(nullptr)
  {
    if (!other.isEmpty()) {
      List< T >* temp = other.head_;
      try {
        while (temp) {
          pushBack(temp->data);
          temp = temp->next;
        }
      } catch (...) {
        clear();
        throw;
      }
    }
  }

  template < typename T >
  ForwardList< T >::ForwardList(ForwardList< T >&& other) noexcept:
    head_(other.head_),
    tail_(other.tail_)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
  }

  template < typename T >
  ForwardList< T >::~ForwardList()
  {
    clear();
  }

  template < typename T >
  void ForwardList< T >::clear()
  {
    List< T >* newHead = nullptr;
    while (head_) {
      newHead = head_->next;
      delete head_;
      head_ = newHead;
    }
    tail_ = nullptr;
  }


  template < typename T >
  T& ForwardList< T >::front()
  {
    if (!head_) {
      throw std::logic_error("List is empty");
    }
    return *this->begin();
  }

  template < typename T >
  const T& ForwardList< T >::front() const {
    if (isEmpty()) {
      throw std::out_of_range("List is empty");
    }
    return head_->begin;
  }

  template < typename T >
  ForwardIter< T > ForwardList< T >::eraseAfter(ForwardConstIter< T > pos)
  {
    if (!pos.cnode_ || !pos.cnode_->next) {
      return ForwardIter< T >(nullptr);
    }
    List< T >* temp = pos.cnode_->next;
    pos.cnode_->next = temp->next;
    delete temp;
    return ForwardIter< T >(pos.cnode_->next);
  }

  template < typename T >
  ForwardList< T >& ForwardList< T >::operator=(const ForwardList< T >& other) {
    if (this != std::addressof(other)) {
      ForwardList< T > temp(other);
      temp.swap(*this);
    }
    return *this;
  }

  template < typename T >
  ForwardList< T >& ForwardList< T >::operator=(ForwardList< T >&& other) {
    if (this != std::addressof(other)) {
      clear();
      swap(other);
    }
    return *this;
  }

  template < typename T >
  ForwardIter< T > ForwardList< T >::insertAfter(ForwardConstIter< T > pos, const T& val)
  {
    if (!pos.cnode_) {
      return ForwardIter< T >(nullptr);
    }
    pos.cnode_->next = new List< T >{val, pos.cnode_->next};
    ++pos;
    return ForwardIter< T >(pos.cnode_);
  }

  template < typename T >
  void ForwardList< T >::swap(ForwardList< T >& other) noexcept
  {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
  }

  template < typename T >
  void ForwardList< T >::pushBack(const T& item)
  {
    if (!head_) {
      head_ = new List< T >{item, nullptr};
      tail_ = head_;
    } else {
      tail_->next = new List< T >{item, nullptr};
      tail_ = tail_->next;
    }
  }

  template < typename T >
  void ForwardList< T >::pushAfter(const ForwardConstIter< T >& iter, const T& item)
  {
    if (!iter.cnode_) {
      head_ = tail_ = new List< T >(item);
      return;
    }
    List< T >* temp = new List< T >(item, iter.cnode_->next);
    if (iter.cnode_->next == nullptr) {
      tail_ = temp;
    }
    iter.cnode_->next = temp;
  }

  template < typename T >
  bool ForwardList< T >::isEmpty() const
  {
    return (head_ == nullptr);
  }

  template < typename T >
  void ForwardList< T >::pushFront(const T& item)
  {
    if (!head_) {
      head_ = new List< T >{item, nullptr};
      tail_ = head_;

    } else {
      List< T >* newHead = new List< T >{item, head_};
      head_ = newHead;
    }
  }

  template < typename T >
  void ForwardList< T >::popFront()
  {
    if (!head_) {
      throw std::logic_error("Underflow");
    } else if (!(head_->next)) {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
      return;
    }
    List< T >* temp = head_;
    head_ = head_->next;
    delete temp;
  }

  template < typename T >
  void ForwardList< T >::popAfter(ForwardIter< T >& iter)
  {
    if (!head_ || iter.cnode_->next == nullptr) {
      throw std::logic_error("There is nothing to delete");
    } else {
      List< T >* subhead = iter.cnode_;
      List< T >* toDelete = subhead->next;
      subhead->next = toDelete->next;
      delete toDelete;
    }
  }

  template < typename T >
  ForwardIter< T > ForwardList< T >::begin() const noexcept
  {
    return ForwardIter< T >(head_);
  }

  template < typename T >
  ForwardIter< T > ForwardList< T >::end() const noexcept
  {
    return ForwardIter< T >(nullptr);
  }

  template < typename T >
  ForwardConstIter< T > ForwardList< T >::cbegin() const noexcept
  {

    return ForwardConstIter< T >(head_);
  }

  template < typename T >
  ForwardConstIter< T > ForwardList< T >::cend() const noexcept
  {
    return ForwardConstIter< T >(nullptr);
  }
}

#endif
