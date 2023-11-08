#ifndef BIDIRECTIONAL_LIST_H
#define BIDIRECTIONAL_LIST_H

#include <iosfwd>
#include <stdexcept>
#include <initializer_list>
#include "BiIterator.h"
#include "ConstBiIterator.h"
#include "List.h"
namespace skarlygina
{
  template < typename T >
  class BidirectionalList: public detail::List< T, detail::BiNode< T > >
  {
  public:
    using BaseList = detail::List< T, detail::BiNode< T > >;
    BidirectionalList();
    BidirectionalList(const BidirectionalList< T >&);
    BidirectionalList(BidirectionalList< T >&&);
    BidirectionalList(std::initializer_list< T >);
    ~BidirectionalList();
    BidirectionalList& operator=(const BidirectionalList< T >&);
    BidirectionalList& operator=(BidirectionalList< T >&&);
    bool operator==(const BidirectionalList< T >&) const;
    bool operator!=(const BidirectionalList< T >&) const;
    void swap(BidirectionalList< T >&) noexcept;
    BiIterator< T > begin();
    BiIterator< T > end();
    ConstBiIterator< T > begin() const;
    ConstBiIterator< T > end() const;
    ConstBiIterator< T > cbegin() const;
    ConstBiIterator< T > cend() const;
    bool isEmpty() const noexcept;
    size_t getSize() const;
    const T& front() const;
    T& front();
    const T& back() const;
    T& back();
    void clear();
    BiIterator< T > insert(BiIterator< T >, const T&);
    BiIterator< T > erase(BiIterator< T >&);
    BiIterator< T > erase(BiIterator< T >&, BiIterator< T >&);
    void pushBack(const T&);
    void pushFront(const T&);
    void popFront();
    void popBack();
    template < typename... Args >
    void emplaceFront(Args&&...);
    template < typename... Args >
    void emplaceBack(Args&&...);
    template < typename... Args >
    void emplace(ConstBiIterator< T >, Args&&...);
  private:
    detail::BiNode< T >* endElem_;
  };
  template < typename T >
  BidirectionalList< T >::BidirectionalList():
    BaseList(),
    endElem_(new detail::BiNode< T >{})
  {}
  template < typename T >
  BidirectionalList< T >::BidirectionalList(const BidirectionalList< T >& other):
    BaseList(),
    endElem_(new detail::BiNode< T >{})
  {
    if (!other.isEmpty())
    {
      auto srcPtr = other.head_;
      do
      {
        pushBack(srcPtr->data_);
        srcPtr = srcPtr->next_;
      }
      while (srcPtr && (srcPtr != other.endElem_));
      BaseList::tail_->next_ = endElem_;
    }
    endElem_->prev_ = BaseList::tail_;
  }
  template < typename T >
  BidirectionalList< T >::BidirectionalList(BidirectionalList< T >&& other):
    BaseList(std::move(other)),
    endElem_(other.endElem_)
  {
    other.endElem_ = nullptr;
    if (!isEmpty())
    {
      endElem_ = BaseList::tail_->next_;
    }
  }
  template < typename T >
  BidirectionalList< T >::BidirectionalList(std::initializer_list< T > list):
    BaseList(),
    endElem_(new detail::BiNode< T >{})
  {
    for (auto && i: list)
    {
      pushBack(i);
    }
    BaseList::tail_->next_ = endElem_;
    endElem_->prev_ = BaseList::tail_;
  }
  template < typename T >
  BidirectionalList< T >::~BidirectionalList()
  {
    clear();
    delete endElem_;
  }
  template < typename T >
  BidirectionalList< T >& BidirectionalList< T >::operator=(const BidirectionalList< T >& other)
  {
    if (this != std::addressof(other))
    {
      auto temp(other);
      swap(temp);
    }
    return *this;
  }
  template < typename T >
  BidirectionalList< T >& BidirectionalList< T >::operator=(BidirectionalList< T >&& other)
  {
    if (this != std::addressof(other))
    {
      swap(other);
      other.clear();
    }
    return *this;
  }
  template < typename T >
  bool BidirectionalList< T >::operator==(const BidirectionalList< T >& other) const
  {
    if ((this != std::addressof(other)) && (BaseList::size_ == other.size_))
    {
      auto thisIt = cbegin();
      auto otherIt = other.cbegin();
      while (thisIt != cend())
      {
        if (*thisIt != *otherIt)
        {
          return false;
        }
        ++thisIt;
        ++otherIt;
      }
      return true;
    }
    return this == std::addressof(other);
  }
  template < typename T >
  bool BidirectionalList< T >::operator!=(const BidirectionalList< T >& other) const
  {
    return !(*this == other);
  }
  template < typename T >
  void BidirectionalList< T >::swap(BidirectionalList< T >& other) noexcept
  {
    BaseList::swap(other);
    std::swap(endElem_, other.endElem_);
  }
  template < typename T >
  bool BidirectionalList< T >::isEmpty() const noexcept
  {
    return BaseList::isEmpty();
  }
  template < typename T >
  size_t BidirectionalList< T >::getSize() const
  {
    return BaseList::getSize();
  }
  template < typename T >
  const T& BidirectionalList< T >::front() const
  {
    return BaseList::front();
  }
  template < typename T >
  T& BidirectionalList< T >::front()
  {
    return const_cast< T& >(BaseList::front());
  }
  template < typename T >
  const T& BidirectionalList< T >::back() const
  {
    return BaseList::back();
  }
  template < typename T >
  T& BidirectionalList< T >::back()
  {
    return const_cast< T& >(BaseList::back());
  }
  template < typename T >
  void BidirectionalList< T >::clear()
  {
    while (!isEmpty())
    {
      popFront();
    }
  }
  template < typename T >
  BiIterator< T > BidirectionalList< T >::insert(BiIterator< T > pos, const T& value)
  {
    auto posPtr = const_cast< detail::BiNode< T >* >(pos.it_.ptr_);
    if (pos == begin())
    {
      pushFront(value);
      return pos;
    }
    else if (pos == end())
    {
      pushBack(value);
      return pos;
    }
    detail::BiNode< T >* temp = posPtr->prev_;
    posPtr->prev_ = new detail::BiNode< T >{value, posPtr, temp};
    temp->next_ = posPtr->prev_;
    ++BaseList::size_;
    return ++pos;
  }
  template < typename T >
  BiIterator< T > BidirectionalList< T >::erase(BiIterator< T >& pos)
  {
    auto posPtr = const_cast< detail::BiNode< T >* >(pos.it_.ptr_);
    if (pos == end())
    {
      throw std::logic_error("Nothing to erase");
    }
    else if (pos == begin())
    {
      popFront();
      pos = begin();
      return pos;
    }
    else if (posPtr == BaseList::tail_)
    {
      popBack();
      pos = --end();
      return pos;
    }
    posPtr->prev_->next_ = posPtr->next_;
    posPtr->next_->prev_ = posPtr->prev_;
    auto temp = posPtr;
    ++pos;
    delete temp;
    --BaseList::size_;
    return pos;
  }
  template < typename T >
  BiIterator< T > BidirectionalList< T >::erase(BiIterator< T >& begin, BiIterator< T >& end)
  {
    while (begin != end)
    {
      erase(begin);
    }
    return begin;
  }
  template < typename T >
  void BidirectionalList< T >::pushBack(const T& data)
  {
    if (!BaseList::size_)
    {
      BaseList::head_ = new detail::BiNode< T >{data, endElem_, nullptr};
      BaseList::tail_ = BaseList::head_;
    }
    else
    {
      BaseList::tail_->next_ = new detail::BiNode< T >{data, endElem_, BaseList::tail_};
      BaseList::tail_ = BaseList::tail_->next_;
    }
    endElem_->prev_ = BaseList::tail_;
    ++BaseList::size_;
  }
  template < typename T >
  void BidirectionalList< T >::pushFront(const T& data)
  {
    if (!BaseList::size_)
    {
      BaseList::head_ = new detail::BiNode< T >{data, endElem_, nullptr};
      BaseList::tail_ = BaseList::head_;
      endElem_->prev_ = BaseList::tail_;
    }
    else
    {
      BaseList::head_->prev_ = new detail::BiNode< T >{data, BaseList::head_, nullptr};
      BaseList::head_ = BaseList::head_->prev_;
    }
    ++BaseList::size_;
  }
  template < typename T >
  void BidirectionalList< T >::popFront()
  {
    if (!BaseList::size_)
    {
      throw std::logic_error("Pop from the empty list");
    }
    if (BaseList::size_ == 1)
    {
      delete BaseList::head_;
      BaseList::head_ = nullptr;
      BaseList::tail_ = nullptr;
      --BaseList::size_;
      endElem_->prev_ = nullptr;
      return;
    }
    detail::BiNode< T >* temp = BaseList::head_;
    BaseList::head_ = BaseList::head_->next_;
    BaseList::head_->prev_ = nullptr;
    delete temp;
    --BaseList::size_;
  }
  template < typename T >
  void BidirectionalList< T >::popBack()
  {
    if (!BaseList::size_)
    {
      throw std::logic_error("Pop from empty list");
    }
    if (BaseList::size_ == 1)
    {
      popFront();
      return;
    }
    detail::BiNode< T >* temp = BaseList::tail_;
    BaseList::tail_ = BaseList::tail_->prev_;
    BaseList::tail_->next_ = endElem_;
    delete temp;
    --BaseList::size_;
    endElem_->prev_ = BaseList::tail_;
  }
  template < typename T >
  BiIterator< T > BidirectionalList< T >::begin()
  {
    return BiIterator< T >(cbegin());
  }
  template < typename T >
  BiIterator< T > BidirectionalList< T >::end()
  {
    return BiIterator< T >(cend());
  }
  template < typename T >
  ConstBiIterator< T > BidirectionalList< T >::begin() const
  {
    return cbegin();
  }
  template < typename T >
  ConstBiIterator< T > BidirectionalList< T >::end() const
  {
    return cend();
  }
  template < typename T >
  ConstBiIterator< T > BidirectionalList< T >::cbegin() const
  {
    return ConstBiIterator< T >(BaseList::head_);
  }
  template < typename T >
  ConstBiIterator< T > BidirectionalList< T >::cend() const
  {
    if (isEmpty())
    {
      return ConstBiIterator< T >(nullptr);
    }
    return ConstBiIterator< T >(endElem_);
  }
  template < typename T >
  template < typename... Args >
  void BidirectionalList< T >::emplaceFront(Args&&... args)
  {
    if (!isEmpty())
    {
      BaseList::head_->prev_ = new detail::BiNode< T >{T(std::forward< Args... >(args...)), BaseList::head_, nullptr};
      BaseList::head_ = BaseList::head_->prev_;
    }
    else
    {
      BaseList::head_ = new detail::BiNode< T >{T(std::forward< Args... >(args...)), endElem_, nullptr};
      BaseList::tail_ = BaseList::head_;
      endElem_->prev_ = BaseList::tail_;
    }
    ++BaseList::size_;
  }
  template < typename T >
  template < typename... Args >
  void BidirectionalList< T >::emplaceBack(Args&&... args)
  {
    if (!isEmpty())
    {
      BaseList::tail_->next_ = new detail::BiNode< T >{T(std::forward< Args... >(args...)), nullptr, BaseList::tail_};
      BaseList::tail_ = BaseList::tail_->next_;
    }
    else
    {
      BaseList::tail_ = new detail::BiNode< T >{T(std::forward< Args... >(args...)), endElem_, nullptr};
      BaseList::head_ = BaseList::tail_;
      endElem_->prev_ = BaseList::tail_;
    }
    ++BaseList::size_;
  }
  template < typename T >
  template < typename... Args >
  void BidirectionalList< T >::emplace(ConstBiIterator< T > pos, Args&&... args)
  {
    if (pos == cbegin())
    {
      emplaceFront(std::forward< Args... >(args...));
    }
    else if (pos == cend())
    {
      emplaceBack(std::forward< Args... >(args...));
    }
    else
    {
      auto posPtr = const_cast< detail::BiNode< T >* >(pos.ptr_);
      auto prev = posPtr->prev_;
      posPtr->prev_ = new detail::BiNode< T >{T(std::forward< Args... >(args...)), posPtr, prev};
      prev->next_ = posPtr->prev_;
    }
    ++BaseList::size_;
  }
}

#endif


