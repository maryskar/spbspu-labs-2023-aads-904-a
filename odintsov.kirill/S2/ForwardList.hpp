#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <cstddef>
#include <initializer_list>

namespace detail {
  template< typename T >
  struct Node {
    T val;
    Node* next;
  };

  template< typename T >
  struct ForwardIterator {
    Node< T >* nodePtr;
    ForwardIterator();

    ForwardIterator& operator++();
    ForwardIterator operator++(int);
    T& operator*();
    T* operator->();

    bool operator==(const ForwardIterator& rhs) const;
    bool operator!=(const ForwardIterator& rhs) const;
  };
}

namespace odintsov {
  template< typename T >
  class ForwardList {
   public:
    using Iter = detail::ForwardIterator< T >;
    using ConstIter = detail::ForwardIterator< const T >;
    ForwardList();

    ForwardList(const ForwardList& fl);
    ForwardList(ForwardList&& fl);
    ForwardList(std::initializer_list< T > il);
    ~ForwardList();

    ForwardList& operator=(const ForwardList& rhs);
    ForwardList& operator=(ForwardList&& rhs);
    ForwardList& operator=(std::initializer_list< T > rhs);

    T& front();
    const T& front() const;

    Iter beforeBegin();
    ConstIter cbeforeBegin() const;
    Iter begin();
    ConstIter cbegin() const;
    Iter end();
    ConstIter cend() const;

    bool empty() const;

    void clear();
    Iter insertAfter(ConstIter pos, const T& val);
    Iter insertAfter(ConstIter pos, T&& val);
    template< class... Args >
    Iter emplaceAfter(ConstIter pos, Args&&... args);
    Iter eraseAfter(ConstIter pos);
    template< class... Args >
    T& emplaceFront(Args&&... args);
    void push(const T& val);
    void push(T&& val);
    void pop();

    void merge(ForwardList& fl);
    void merge(ForwardList&& fl);
    void spliceAfter(ConstIter pos, ForwardList& fl);
    void spliceAfter(ConstIter pos, ForwardList&& fl);
    void remove(const T& val);
    template< class UnaryPredicate >
    void removeIf(UnaryPredicate c);
    void reverse();
  };
}

#endif
