#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include <stdexcept>
#include "ForwardIter.h"
#include "ForwardConstIter.h"
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
    ForwardList(const ForwardList< T > &val);
    ForwardList(ForwardList< T > &&val) noexcept;

    ForwardList< T > &operator=(const ForwardList< T > &val);
    ForwardList< T > &operator=(ForwardList< T > &&val) noexcept;

    iter before_begin() noexcept;
    constIter before_begin() const noexcept;
    constIter cbefore_begin() const noexcept;
    iter begin() noexcept;
    constIter begin() const noexcept;
    constIter cbegin() const noexcept;
    iter end() noexcept;
    constIter end() const noexcept;
    constIter cend() const noexcept;

    void remove(const T &value);
    template<typename Comparator>
    void remove_if(Comparator p);

    bool empty() const noexcept;
    void clear() noexcept;
    void swap(ForwardList< T > &val);

    T & front();
    template< typename Input >
    iter insert_after(Input pos, const T & val);
    iter insert_after(constIter pos, T &&val);
    iter insert_after(constIter pos, size_t count, const T & val);
    iter insert_after(constIter pos, iter first, iter last);

    void push_front(const T & val);
    void push_front(T &&val);
    void pop_front();

    iter erase_after(constIter pos);
    iter erase_after(constIter first, constIter last);

    void splice_after(constIter pos, ForwardList< T > &other);
    void splice_after(constIter pos, ForwardList< T > &&other);

    template<typename ...Args>
    iter emplace_after(constIter pos, Args &&...args);
    iter emplace_front(constIter pos);
  private:
    List< T > *fakenode_;
    List< T > *tail_;
    void Fcopy(const ForwardList< T > &rhs);
  };

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
    return iter(newNode);
  }
  template< typename T >
  ForwardList< T >::ForwardList():
    fakenode_(static_cast< List< T >* >(::operator new(sizeof(List< T >)))),
    tail_(nullptr)
  {
    fakenode_->next = tail_;
  }

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    clear();
    ::operator delete(fakenode_);
  }

  template< typename T >
  ForwardList< T >::ForwardList(const ForwardList< T > &val):
    ForwardList()
  {
    Fcopy(val);
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
      }
      else
      {
        previous = current;
      }
    }
    fakenode_->next = previous;
  }

  template< typename T >
  ForwardList< T >::ForwardList(ForwardList< T > &&val) noexcept:
    ForwardList()
  {
    swap(val);
    val.tail_ = nullptr;
    val.fakenode_->next = nullptr;
  }

  template< typename T >
  ForwardList< T > &ForwardList< T >::operator=(const ForwardList< T > &val)
  {
    if (this == std::addressof(val))
    {
      return *this;
    }
    clear();
    Fcopy(val);
    return *this;
  }

  template< typename T >
  ForwardList< T > &ForwardList< T >::operator=(ForwardList< T > &&val) noexcept
  {
    if (this == std::addressof(val))
    {
      return *this;
    }
    clear();
    fakenode_->next = val.fakenode_->next;
    tail_ = val.tail_;
    val.fakenode_->next = nullptr;
    val.tail_ = nullptr;
    return *this;
  }

  template< typename T >
  typename ForwardList< T >::iter ForwardList< T >::before_begin() noexcept
  {
    return iter(fakenode_);
  }

  template< typename T >
  typename ForwardList< T >::constIter ForwardList< T >::before_begin() const noexcept
  {
    return cbefore_begin();
  }

  template< typename T >
  typename ForwardList< T >::constIter ForwardList< T >::cbefore_begin() const noexcept
  {
    return constIter(fakenode_);
  }

  template< typename T >
  typename ForwardList< T >::iter ForwardList< T >::begin() noexcept
  {
    return iter(fakenode_->next);
  }

  template< typename T >
  typename ForwardList< T >::constIter ForwardList< T >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename T >
  typename ForwardList< T >::constIter ForwardList< T >::cbegin() const noexcept
  {
    return constIter(fakenode_->next);
  }

  template< typename T >
  typename ForwardList< T >::iter ForwardList< T >::end() noexcept
  {
    return iter(nullptr);
  }

  template< typename T >
  typename ForwardList< T >::constIter ForwardList< T >::end() const noexcept
  {
    return cend();
  }

  template< typename T >
  typename ForwardList< T >::constIter ForwardList< T >::cend() const noexcept
  {
    return constIter(nullptr);
  }

  template< typename T >
  bool ForwardList< T >::empty() const noexcept
  {
    return fakenode_->next == tail_;
  }

  template <typename T>
  void ForwardList<T>::clear() noexcept
  {
    clearlist(fakenode_->next);
    tail_ = nullptr;
  }

  template< typename T >
  void ForwardList< T >::swap(ForwardList< T > &val)
  {
    std::swap(fakenode_, val.fakenode_);
    std::swap(tail_, val.tail_);
    std::swap(fakenode_->next, val.fakenode_->next);
  }

  template< typename T >
  T &ForwardList< T >::front()
  {
    return fakenode_->next->data;
  }

  template< typename T >
  template< typename Input>
  typename ForwardList< T >::iter ForwardList< T >::insert_after(Input pos, const T & val)
  {
    if (!pos.node_)
    {
      throw std::invalid_argument("invalid_argument");
    }
    auto newNode = new List< T >{val, nullptr};
    if (pos.node_ == fakenode_)
    {
      newNode->next = fakenode_->next;
      fakenode_->next = newNode;
      if (tail_ == fakenode_)
      {
        tail_->next = newNode;
        tail_ = newNode;
      }
    }
    else
    {
      newNode->next = pos.node_->next;
      pos.node_->next = newNode;
      if (pos.node_ == tail_)
      {
        tail_->next = newNode;
        tail_ = newNode;
      }
    }
    return iter(newNode);
  }

  template< typename T >
  typename ForwardList< T >::iter ForwardList< T >::insert_after(constIter pos, T &&val)
  {
    return insert_after(pos, val);
  }

  template< typename T >
  typename ForwardList< T >::iter ForwardList< T >::insert_after(constIter pos, size_t count, const T & val)
  {
    for (size_t i = 0; i < count; i++)
    {
      pos = insert_after(pos, val);
      pos++;
    }
    return pos;
  }

  template< class T >
  typename ForwardList< T >::iter ForwardList< T >::insert_after(constIter pos, iter first, iter last)
  {
    while (first != last)
    {
      pos = insert_after(pos, *first);
      pos++;
      first++;
    }
    return pos;
  }


  template< typename T >
  void ForwardList< T >::push_front(const T & val)
  {
    insert_after(cbefore_begin(), val);
  }

  template< typename T >
  void ForwardList< T >::push_front(T &&val)
  {
    insert_after(cbefore_begin(), std::move(val));
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
  }

  template < typename T >
  typename ForwardList< T >::iter ForwardList< T >::erase_after(constIter pos)
  {
    if (pos.node_ == nullptr || pos.node_->next == nullptr)
    {
      return end();
    }
    List< T > *todel = pos.node_->next;
    pos.node_->next = todel->next;
    if (todel == tail_)
    {
      tail_ = pos.node_;
    }
    if(todel == fakenode_->next)
    {
      fakenode_->next = fakenode_->next->next;
    }
    delete todel;
    return iter(pos.node_->next);
  }

  template < typename T >
  typename ForwardList< T >::iter timofeev::ForwardList< T >::erase_after(constIter first, constIter last)
  {
    if (first == last || first.node_ == nullptr)
    {
      return end();
    }
    constIter cur = first;
    while (cur.node_->next != last.node_->next)
    {
      erase_after(cur);
    }
    return iter(last.node_->next);
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
  void ForwardList< T >::Fcopy(const ForwardList< T > &rhs)
  {
    auto tmp = copy(rhs.fakenode_->next);
    fakenode_->next = tmp.first;
    tail_ = tmp.second;
  }
}
#endif
