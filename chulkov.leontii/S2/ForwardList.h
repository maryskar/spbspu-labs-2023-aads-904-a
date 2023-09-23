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
  class FrdList
  {
  public:
    FrdList();
    FrdList(const FrdList& other);
    FrdList(FrdList&& other) noexcept;
    ~FrdList();
    void clear();

    void swap(FrdList& other) noexcept;
    void pushFront(const T& item);
    void popFront();
    void popAfter(ForwardIter< T >& iter);
    void pushBack(const T& item);
    void pushAfter(const ForwardConstIter< T >& iter, const T& item);
    bool isEmpty() const;
    T& front();

    ForwardIter< T > insertAfter(ForwardConstIter< T >, const T&);
    ForwardIter< T > eraseAfter(ForwardConstIter< T > it);
    ForwardIter< T > begin() noexcept;
    ForwardIter< T > end() noexcept;
    ForwardConstIter< T > cbegin() const noexcept;
    ForwardConstIter< T > cend() const noexcept;

  private:
    List< T >* head_;
    List< T >* tail_;
  };

  template < typename T >
  FrdList< T >::FrdList():
    head_(nullptr),
    tail_(nullptr)
  {}

  template < typename T >
  FrdList< T >::FrdList(const FrdList< T >& other):
    head_(nullptr),
    tail_(nullptr)
  {
    if (!other.isEmpty()) {
      List< T >* temp = other.head_;
      try {
        while (temp) {
          pushBack(temp->item_);
          temp = temp->next_;
        }
      } catch (...) {
        clear();
        throw;
      }
    }
  }

  template < typename T >
  FrdList< T >::FrdList(FrdList< T >&& other) noexcept:
    head_(other.head_),
    tail_(other.tail_)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
  }

  template < typename T >
  FrdList< T >::~FrdList()
  {
    clear();
  }

  template < typename T >
  void FrdList< T >::clear()
  {
    List< T >* newHead = nullptr;
    while (head_) {
      newHead = head_->next_;
      delete head_;
      head_ = newHead;
    }
    tail_ = nullptr;
  }

  template < typename T >
  T& FrdList< T >::front()
  {
    if (!head_) {
      throw std::logic_error("List is empty");
    }
    return *this->begin();
  }

  template < typename T >
  ForwardIter< T > FrdList< T >::eraseAfter(ForwardConstIter< T > pos)
  {
    if (!pos.cnode_ || !pos.cnode_->next_) {
      return ForwardIter< T >(nullptr);
    }
    List< T >* temp = pos.cnode_->next_;
    pos.cnode_->next_ = temp->next_;
    delete temp;
    return ForwardIter< T >(pos.cnode_->next_);
  }

  template < typename T >
  ForwardIter< T > FrdList< T >::insertAfter(ForwardConstIter< T > pos, const T& val)
  {
    if (!pos.cnode_) {
      return ForwardIter< T >(nullptr);
    }
    pos.cnode_->next_ = new List< T >{val, pos.cnode_->next_};
    ++pos;
    return ForwardIter< T >(pos.cnode_);
  }

  template < typename T >
  void FrdList< T >::swap(FrdList< T >& other) noexcept
  {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
  }

  template < typename T >
  void FrdList< T >::pushBack(const T& item)
  {
    if (!head_) {
      head_ = new List< T >{item, nullptr};
      tail_ = head_;
    } else {
      tail_->next_ = new List< T >{item, nullptr};
      tail_ = tail_->next_;
    }
  }

  template < typename T >
  void FrdList< T >::pushAfter(const ForwardConstIter< T >& iter, const T& item)
  {
    if (!iter.cnode_) {
      head_ = tail_ = new List< T >(item);
      return;
    }
    List< T >* temp = new List< T >(item, iter.cnode_->next_);
    if (iter.cnode_->next_ == nullptr) {
      tail_ = temp;
    }
    iter.cnode_->next_ = temp;
  }

  template < typename T >
  bool FrdList< T >::isEmpty() const
  {
    return (head_ == nullptr);
  }

  template < typename T >
  void FrdList< T >::pushFront(const T& item)
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
  void FrdList< T >::popFront()
  {
    if (!head_) {
      throw std::logic_error("Underflow");
    } else if (!(head_->next_)) {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
      return;
    }
    List< T >* temp = head_;
    head_ = head_->next_;
    delete temp;
  }

  template < typename T >
  void FrdList< T >::popAfter(ForwardIter< T >& iter)
  {
    if (!head_ || iter.cnode_->next_ == nullptr) {
      throw std::logic_error("There is nothing to delete");
    } else {
      List< T >* subhead = iter.cnode_;
      List< T >* toDelete = subhead->next_;
      subhead->next_ = toDelete->next_;
      delete toDelete;
    }
  }

  template < typename T >
  ForwardIter< T > FrdList< T >::begin() noexcept
  {
    return ForwardIter< T >(head_);
  }

  template < typename T >
  ForwardIter< T > FrdList< T >::end() noexcept
  {
    return ForwardIter< T >(nullptr);
  }

  template < typename T >
  ForwardConstIter< T > FrdList< T >::cbegin() const noexcept
  {

    return ForwardConstIter< T >(head_);
  }

  template < typename T >
  ForwardConstIter< T > FrdList< T >::cend() const noexcept
  {
    return ForwardConstIter< T >(nullptr);
  }
}

#endif
