#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

namespace detail {
  template< typename T >
  struct Node {
    Node* next;
    T val;
  };

  template< typename T >
  struct ForwardIterator: public std::iterator< std::forward_iterator_tag, T > {
    Node< T >* nodePtr;

    ForwardIterator():
      nodePtr(nullptr)
    {}

    ForwardIterator(Node< T >* ptr):
      nodePtr(ptr)
    {}

    ForwardIterator& operator++()
    {
      if (nodePtr) {
        nodePtr = nodePtr->next;
      }
      return *this;
    }

    ForwardIterator operator++(int)
    {
      ForwardIterator< T > copy(*this);
      if (nodePtr) {
        nodePtr = nodePtr->next;
      }
      return copy;
    }

    T& operator*() const
    {
      return nodePtr->data;
    }

    T* operator->() const
    {
      return std::addressof(nodePtr->data);
    }

    bool operator==(const ForwardIterator& rhs) const
    {
      return nodePtr == rhs.nodePtr;
    }

    bool operator!=(const ForwardIterator& rhs) const
    {
      return nodePtr != rhs.nodePtr;
    }
  };

  template< typename T >
  struct ConstForwardIterator: public std::iterator< std::forward_iterator_tag, T > {
    const Node< T >* nodePtr;

    ConstForwardIterator():
      nodePtr(nullptr)
    {}

    ConstForwardIterator(const Node< T >* ptr):
      nodePtr(ptr)
    {}

    ConstForwardIterator& operator++()
    {
      if (nodePtr) {
        nodePtr = nodePtr->next;
      }
      return *this;
    }

    ConstForwardIterator operator++(int)
    {
      ConstForwardIterator< T > copy(*this);
      if (nodePtr) {
        nodePtr = nodePtr->next;
      }
      return copy;
    }

    const T& operator*() const
    {
      return nodePtr->data;
    }

    const T* operator->() const
    {
      return std::addressof(nodePtr->data);
    }

    bool operator==(const ConstForwardIterator& rhs) const
    {
      return nodePtr == rhs.nodePtr;
    }

    bool operator!=(const ConstForwardIterator& rhs) const
    {
      return nodePtr != rhs.nodePtr;
    }
  };

}

namespace odintsov {
  template< typename T >
  class ForwardList {
   public:
    using Iter = detail::ForwardIterator< T >;
    using ConstIter = detail::ConstForwardIterator< T >;
    using Node = detail::Node< T >;

    ForwardList():
      ForwardList(nullptr)
    {}

    ForwardList(const ForwardList& fl):
      ForwardList()
    {
      unsafeSpliceAfter(cbeforeBegin(), fl.cbegin(), fl.cend());
    }

    ForwardList(ForwardList&& fl):
      ForwardList(fl.head_)
    {
      fl.head_ = nullptr;
    }

    ForwardList(std::initializer_list< T > il):
      ForwardList()
    {
      unsafeInsertAfter(cbeforeBegin(), il);
    }

    ~ForwardList()
    {
      clear();
    }

    ForwardList& operator=(const ForwardList& rhs)
    {
      if (this == std::addressof(rhs)) {
        return *this;
      }
      ConstIter initBegin = cbegin();
      try {
        Iter last = unsafeInsertAfter(cbeforeBegin(), rhs.cbegin(), rhs.cend());
        unsafeEraseAfter(last, cend());
      } catch (const std::bad_alloc&) {
        unsafeEraseAfter(cbeforeBegin(), initBegin);
        throw;
      }
      return *this;
    }

    ForwardList& operator=(ForwardList&& rhs)
    {
      if (this == std::addressof(rhs)) {
        return *this;
      }
      clear();
      *head() = *rhs.head();
      *rhs.head() = nullptr;
      return *this;
    }

    ForwardList& operator=(std::initializer_list< T > rhs)
    {
      ConstIter initBegin = cbegin();
      try {
        Iter last = unsafeInsertAfter(cbeforeBegin(), rhs);
        unsafeEraseAfter(last, cend());
      } catch (const std::bad_alloc&) {
        unsafeEraseAfter(cbeforeBegin(), initBegin);
        throw;
      }
      return *this;
    }

    T& front()
    {
      return const_cast< T& >(const_cast< const ForwardList* >(this)->front());
    }

    const T& front() const
    {
      if (empty()) {
        throw std::logic_error("Attempt to call front() on empty ForwardList");
      }
      return unsafeFront();
    }

    T& unsafeFront()
    {
      return (*head())->data;
    }

    const T& unsafeFront() const
    {
      return (*head())->data;
    }

    Iter beforeBegin()
    {
      return Iter(preHead_);
    }

    ConstIter cbeforeBegin() const
    {
      return ConstIter(preHead_);
    }

    Iter begin()
    {
      return Iter(*head());
    }

    ConstIter cbegin() const
    {
      return ConstIter(*head());
    }

    Iter end()
    {
      return Iter();
    }

    ConstIter cend() const
    {
      return ConstIter();
    }

    bool empty() const
    {
      return !*head();
    }

    void clear()
    {
      while (!empty()) {
        popFront();
      }
    }

    Iter insertAfter(ConstIter pos, const T& val)
    {
      assertIterInside(pos);
      return unsafeInsertAfter(pos, val);
    }

    Iter unsafeInsertAfter(ConstIter pos, const T& val)
    {
      return unsafeInsertAfter(pos, new Node{nullptr, val});
    }

    Iter insertAfter(ConstIter pos, T&& val)
    {
      assertIterInside(pos);
      return unsafeInsertAfter(pos, val);
    }

    Iter unsafeInsertAfter(ConstIter pos, T&& val)
    {
      return unsafeInsertAfter(pos, new Node{nullptr, val});
    }

    template< class InputIter >
    Iter insertAfter(ConstIter pos, InputIter first, InputIter last)
    {
      assertIterInside(pos);
      return unsafeInsertAfter(pos, first, last);
    }

    template< class InputIter >
    Iter unsafeInsertAfter(ConstIter pos, InputIter first, InputIter last)
    {
      Iter lastInserted(const_cast< Node* >(pos.nodePtr));
      while (first != last) {
        lastInserted = unsafeInsertAfter(lastInserted, *first);
        ++first;
      }
      return lastInserted;
    }

    Iter insertAfter(ConstIter pos, std::initializer_list< T > il)
    {
      assertIterInside(pos);
      return unsafeInsertAfter(pos, il);
    }

    Iter unsafeInsertAfter(ConstIter pos, std::initializer_list< T > il)
    {
      return unsafeInsertAfter(pos, il.begin(), il.end());
    }

    template< class... Args >
    Iter emplaceAfter(ConstIter pos, Args&&... args)
    {
      assertIterInside(pos);
      unsafeInsertAfter(pos, new Node{nullptr, T(std::forward< Args >(args)...)});
    }

    template< class... Args >
    Iter unsafeEmplaceAfter(ConstIter pos, Args&&... args)
    {
      unsafeInsertAfter(pos, new Node{nullptr, T(std::forward< Args >(args)...)});
    }

    Iter eraseAfter(ConstIter pos)
    {
      assertIterInside(pos);
      return unsafeEraseAfter(pos);
    }

    Iter unsafeEraseAfter(ConstIter pos)
    {
      const Node* nextNode = pos.nodePtr->next;
      Node* posPtr = const_cast< Node* >(pos.nodePtr);
      posPtr->next = const_cast< Node* >(nextNode->next);
      delete nextNode;
      return Iter(posPtr->next);
    }

    Iter eraseAfter(ConstIter first, ConstIter last)
    {
      assertIterInside(first);
      return unsafeEraseAfter(first, last);
    }

    Iter unsafeEraseAfter(ConstIter first, ConstIter last)
    {
      const ConstIter end = cend();
      for (ConstIter next = std::next(first); next != last && next != end; next = std::next(first)) {
        eraseAfter(first);
      }
    }

    template< class... Args >
    T& emplaceFront(Args&&... args)
    {
      pushFront(new Node{nullptr, T(std::forward< Args >(args)...)});
    }

    void pushFront(const T& val)
    {
      pushFront(new Node{nullptr, val});
    }

    void pushFront(T&& val)
    {
      pushFront(new Node{nullptr, std::move(val)});
    }

    void popFront()
    {
      if (empty()) {
        throw std::logic_error("Attempt to pop empty ForwardList");
      }
      unsafePopFront();
    }

    void unsafePopFront()
    {
      Node* next = (*head())->next;
      delete *head();
      *head() = next;
    }

    void swap(ForwardList& fl)
    {
      std::swap(*head(), *fl.head());
    }

    void merge(ForwardList& fl)
    {
      if (this == std::addressof(fl)) {
        return;
      }
      unsafeSpliceAfter(cbeforeBegin(), fl);
    }

    void merge(ForwardList&& fl)
    {
      if (this == std::addressof(fl)) {
        return;
      }
      unsafeSpliceAfter(cbeforeBegin(), fl);
    }

    void spliceAfter(ConstIter pos, ForwardList& fl)
    {
      assertIterInside(pos);
      if (this == std::addressof(fl)) {
        return;
      }
      unsafeSpliceAfter(pos, fl);
    }

    void unsafeSpliceAfter(ConstIter pos, ForwardList& fl)
    {
      Node* next = const_cast< Node* >(pos.nodePtr)->next;
      const_cast< Node* >(pos.nodePtr)->next = *fl.head;
      while (pos.nodePtr->next != nullptr) {
        ++pos;
      }
      const_cast< Node* >(pos.nodePtr)->next = next;
      *fl.head() = nullptr;
    }

    void spliceAfter(ConstIter pos, ForwardList&& fl)
    {
      assertIterInside(pos);
      if (this == std::addressof(fl)) {
        return;
      }
      unsafeSpliceAfter(pos, fl);
    }

    void unsafeSpliceAfter(ConstIter pos, ForwardList&& fl)
    {
      Node* next = const_cast< Node* >(pos.nodePtr)->next;
      const_cast< Node* >(pos.nodePtr)->next = *fl.head();
      while (pos.nodePtr->next != nullptr) {
        ++pos;
      }
      const_cast< Node* >(pos.nodePtr)->next = next;
      *fl.head() = nullptr;
    }

    void remove(const T& val)
    {
      const ConstIter end = cend();
      for (ConstIter iter = cbeforeBegin(); iter.nodePtr->next != nullptr;) {
        if (iter.nodePtr->next->val == val) {
          eraseAfter(iter);
        } else {
          ++iter;
        }
      }
    }

    template< class UnaryPredicate >
    void removeIf(UnaryPredicate check)
    {
      const ConstIter end = cend();
      for (ConstIter iter = cbeforeBegin(); iter.nodePtr->next != nullptr;) {
        if (check(iter.nodePtr->next->val)) {
          eraseAfter(iter);
        } else {
          ++iter;
        }
      }
    }

    void reverse()
    {
      Node* lastPtr = nullptr;
      const ConstIter end = cend();
      for (ConstIter iter = begin(); iter != end; ++iter) {
        iter.nodePtr->next = lastPtr;
        lastPtr = iter.nodePtr;
      }
      *head() = lastPtr;
    }

   private:
    Node* preHead_;

    ForwardList(Node* headPtr):
      preHead_(reinterpret_cast< Node* >(::operator new(sizeof(Node))))
    {
      preHead_->next = headPtr;
    }

    Node** head()
    {
      return preHead_ ? std::addressof(preHead_->next) : nullptr;
    }

    void assertIterInside(ConstIter it)
    {
      if (it == cend()) {
        throw std::range_error("Invalid attempt to use iterator outside ForwardList");
      }
    }

    Iter unsafeInsertAfter(ConstIter pos, Node* n)
    {
      Node* prevNode = const_cast< Node* >(pos.nodePtr);
      n->next = prevNode->next;
      prevNode->next = n->next;
      return Iter(n);
    }

    void pushFront(Node* n)
    {
      n->next = (*head())->next;
      (*head())->next = n;
    };
  };

  template< typename T >
  bool operator==(const ForwardList< T >& lhs, const ForwardList< T >& rhs)
  {
    typename ForwardList< T >::ConstIter lend = lhs.cend();
    typename ForwardList< T >::ConstIter rend = rhs.cend();
    typename ForwardList< T >::ConstIter liter = lhs.cbegin();
    typename ForwardList< T >::ConstIter riter = rhs.cbegin();
    for (; liter != lend && riter != rend; ++liter, ++riter) {
      if (!(*liter == *riter)) {
        return false;
      }
    }
    return liter == lend && riter == rend;
  }

  template< typename T >
  bool operator!=(const ForwardList< T >& lhs, const ForwardList< T >& rhs)
  {
    return !(lhs == rhs);
  }
}

#endif
