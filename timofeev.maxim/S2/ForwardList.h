#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <cstddef>
#include <stdexcept>
#include "ForwardIter.h"
#include "ForwardConstIter.h"
//#include <List.h>
#include "../common/List.h"
namespace timofeev
{
  template< typename T >
  class ForwardList
  {
  public:
    using iter = ForwardIterator< T >;
    using constIter = ForwardConstIterator< T >;

    ForwardList();
    ~ForwardList();
    ForwardList(const ForwardList< T > &lhs);
    ForwardList(ForwardList< T > &&rhs) noexcept;

    ForwardList< T > &operator=(const ForwardList< T > &rhs);
    ForwardList< T > &operator=(ForwardList< T > &&rhs) noexcept;

    bool empty() const;
    void clear();
    iter before_begin() noexcept;
    constIter before_begin() const noexcept;
    iter begin() noexcept;
    constIter begin() const noexcept;
    iter end() noexcept;
    constIter end() const noexcept;
    constIter cbegin() const noexcept;
    constIter cend() const noexcept;

    constIter cbefore_begin() const noexcept;

    iter insert_after(constIter pos, const T &value);
    iter insert_after(constIter pos, T &&value);
    iter insert_after(constIter pos, size_t count, const T &value);
    iter insert_after(constIter pos, iter first, iter last);

    T &front();

    iter erase_after(constIter pos);
    iter erase_after(constIter first, constIter last);

    template<typename ...Args>
    iter emplace_after(constIter pos, Args &&...args);
    iter emplace_front(constIter pos);

    void push_front(const T &value);
    void push_front(T &&value);
    void pop_front();

    void swap(ForwardList< T > &other) noexcept;

    void splice_after(constIter pos, ForwardList< T > &other);
    void splice_after(constIter pos, ForwardList< T > &&other);

    void remove(const T &value);
    template<typename Comparator>
    void remove_if(Comparator p);

    size_t size() const

    noexcept;

  private:
    List< T > *fakenode_;
    List< T > *tail_;
    size_t size_;
  };

  template< typename T >
  T &ForwardList< T >::front()
  {
    return fakenode_->next->data;
  }

  template< typename T >
  typename ForwardList< T >::iter ForwardList< T >::erase_after(constIter pos)
  {
    if (pos.node_ == nullptr || pos.node_->next == nullptr)
    {
      return end();
    }
    List< T > *tmp = pos.node_->next;
    pos.node_->next = tmp->next;
    delete tmp;
    return iter(pos.node_->next);
  }

  template< typename T >
  typename ForwardList< T >::iter ForwardList< T >::erase_after(constIter first, constIter last)
  {
    size_t count = last - first;
    for (size_t i = 0; i < count; i++)
    {
      erase_after(first);
    }
    return last;
  }

  template< typename T >
  void ForwardList< T >::splice_after(constIter pos, ForwardList< T > &other)
  {
    if (other.empty())
    {
      return;
    }
    constIter lastElem = other.cend();
    while (lastElem.node_->next != nullptr)
    {
      ++lastElem;
    }
    size_ += other.size();
    other.size_ = 0;
    lastElem.node_->next = pos.node_->next;
    pos.node_->next = other.tail_->next;
    other.fakenode_->next->next = nullptr;
  }

  template< typename T >
  void ForwardList< T >::splice_after(constIter pos, ForwardList< T > &&other)
  {
    splice_after(pos, other);
  }

  template< typename T >
  void ForwardList< T >::swap(ForwardList< T > &other) noexcept
  {
    std::swap(fakenode_, other.fakenode_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  template< typename T >
  void ForwardList< T >::remove(const T &value)
  {
    List< T > *previous = &fakenode_->next;
    while (previous->next != nullptr)
    {
      List< T > *current = static_cast<List< T > *>(previous->next);
      if (current->data == value)
      {
        previous->next = current->next;
        delete current;
        size_--;
      }
      else
      {
        previous = current;
      }
    }
    fakenode_->next = previous;
  }

  template< typename T >
  template< typename Comparator >
  void ForwardList< T >::remove_if(Comparator p)
  {
    List< T > *previous = &fakenode_->next;
    while (previous->next != nullptr)
    {
      List< T > *current = static_cast< List< T > * >(previous->next);
      if (p(current->data))
      {
        previous->next = current->next;
        delete current;
        size_--;
      }
      else
      {
        previous = current;
      }
    }
    fakenode_->next = previous;
  }

  template< typename T >
  template< typename ...Args >
  ForwardIterator < T > ForwardList< T >::emplace_after(constIter pos, Args &&...args)
  {
    auto newNode = new List< T >(std::forward<Args>(args)...);
    if (!newNode)
    {
      throw std::bad_alloc();
    }
    newNode->next = pos.node_->next;
    pos.node_->next = newNode;
    ++size_;
    return iter(newNode);
  }

  template< typename T >
  ForwardIterator < T > ForwardList< T >::emplace_front(constIter pos)
  {
    auto newNode = new List< T >();
    if (!newNode)
    {
      throw std::bad_alloc();
    }
    newNode->next = pos.node_;
    pos.node_ = newNode;
    ++size_;
    return iter(newNode);
  }

  template< typename T >
  void ForwardList< T >::push_front(T &&val)
  {
    insert_after(cbefore_begin(), std::move(val));
  }

  template< typename T >
  void ForwardList< T >::push_front(const T &value)
  {
    List< T > *newNode = new List< T >{value, nullptr};
    if (!fakenode_ || !fakenode_->next)
    {
      fakenode_->next = newNode;
      tail_ = fakenode_->next;
      return;
    }
    newNode->next = fakenode_->next;
    fakenode_->next = newNode;
  }

  template< typename T >
  typename ForwardList< T >::iter ForwardList< T >::insert_after(constIter pos, T &&value)
  {
    return insert_after(pos, value);
  }

  template< typename T >
  typename ForwardList< T >::iter
  ForwardList< T >::insert_after(constIter pos, size_t count, const T &value)
  {
    for (size_t i = 0; i < count; i++)
    {
      pos = insert_after(pos, value);
      pos++;
      size_++;
    }
    return pos;
  }

  template< typename T >
  typename ForwardList< T >::iter ForwardList< T >::insert_after(constIter pos,
    iter first, iter last)
  {
    while (first != last)
    {
      pos = insert_after(pos, *first);
      pos++;
      first++;
      size_++;
    }
    return pos;
  }

  template <typename T >
  typename ForwardList< T >::iter ForwardList< T >::insert_after(constIter pos, const T &value)
  {
    if (!fakenode_ || !fakenode_->next)
    {
      push_front(value);
      size_++;
      return iter(pos.node_->next);
    }
    if (cbegin() == pos)
    {
      List< T > *newNode = new List< T >{value, nullptr};
      newNode->next = tail_->next;
      tail_->next = newNode;
      size_++;
      return iter(newNode);
    }
    auto *newNode = new List< T >{value, nullptr};
    List< T > *prev = pos.node_;
    newNode->next = prev->next;
    prev->next = newNode;
    size_++;
    return iter(newNode);
  }

  template< typename T >
  typename ForwardList< T >::constIter ForwardList< T >::cbefore_begin() const noexcept
  {
    return constIter(fakenode_);
  }

  template< typename T >
  typename ForwardList< T >::constIter ForwardList< T >::cend() const noexcept
  {
    return end();
  }

  template< typename T >
  typename ForwardList< T >::constIter ForwardList< T >::cbegin() const noexcept
  {
    return constIter(fakenode_->next);
  }

  template< typename T >
  typename ForwardList< T >::iter ForwardList< T >::end() noexcept
  {
    return iter(tail_);
  }

  template< typename T >
  typename ForwardList< T >::constIter ForwardList< T >::end() const noexcept
  {
  return constIter(tail_);
  }

  template< typename T >
  typename ForwardList< T >::iter ForwardList< T >::begin() noexcept
  {
  return iter(fakenode_->next);
  }

  template< typename T >
  typename ForwardList< T >::constIter ForwardList< T >::begin() const noexcept
  {
  return constIter(fakenode_->next);
  }

  template< typename T >
  typename ForwardList< T >::constIter ForwardList< T >::before_begin() const noexcept
  {
  return cbefore_begin();
  }

  template< typename T >
  typename ForwardList< T >::iter ForwardList< T >::before_begin() noexcept
  {
  return iter(fakenode_);
  }

  template< typename T >
  ForwardList< T > &ForwardList< T >::operator=(ForwardList< T > &&rhs) noexcept
  {
    if (this == std::addressof(rhs))
    {
      return *this;
    }
    insert_after(before_begin(), rhs.begin(), rhs.end());
    return *this;
  }

  template< typename T >
  ForwardList< T > &ForwardList< T >::operator=(const ForwardList< T > &rhs)
  {
    if (this != &rhs)
    {
      clear();
      List< T >* cur = rhs.fakenode_->next;
      while (cur != nullptr)
      {
        insert_after(tail_,cur->data);
        cur = cur->next;
      }
    }
    return *this;
  }

  template< typename T >
  ForwardList< T >::ForwardList(ForwardList< T > &&rhs) noexcept:
    fakenode_(rhs.fakenode_),
    tail_(rhs.tail_),
    size_(rhs.size_)
  {
    rhs.fakenode_ = nullptr;
    rhs.tail_ = nullptr;
    rhs.size_ = 0;
  }

  template< typename T >
  ForwardList< T >::ForwardList(const ForwardList< T > &lhs)
  {
    fakenode_ = new List< T >;
    List< T >* tmp = fakenode_;
    List< T >* src = lhs.fakenode_;
    while (src->next != nullptr)
    {
      tmp->next = new List< T >(src->next->data);
      tmp = tmp->next;
      src = src->next;
    }
    tail_ = tmp;
    size_ = lhs.size_;
  }

  template< typename T >
  ForwardList< T >::ForwardList():
    fakenode_(new List< T >),
    tail_(fakenode_),
    size_(0)
  {}

  template< typename T >
  void ForwardList< T >::clear()
  {
    List<T>* cur = fakenode_->next;
    List<T>* next = nullptr;
    while (cur != nullptr) {
      next = cur->next;
      delete cur;
      cur = next;
    }
    tail_ = fakenode_;
    fakenode_->next = nullptr;
    size_ = 0;
  }

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    clear();
    delete fakenode_;
  }

  template< typename T >
  size_t ForwardList< T >::size() const noexcept
  {
    return size_;
  }

  template< typename T >
  void ForwardList< T >::pop_front()
  {
    if (!fakenode_->next)
    {
      throw std::out_of_range("out of range");
    }
    List< T > *tmp = fakenode_->next;
    delete fakenode_->next;
    fakenode_->next = fakenode_->next;
    size_--;
  }

  template< typename T >
  bool ForwardList< T >::empty() const
  {
    return fakenode_->next == tail_;
  }
}
#endif
