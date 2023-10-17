#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

#include <Node.hpp>

namespace odintsov {
  template< typename T >
  class ForwardList {
    using Node = ::detail::Node< T >;

   public:
    struct ConstIter;

    struct Iter: public std::iterator< std::forward_iterator_tag, T > {
      friend ForwardList;
      friend ConstIter;

      Iter():
        nodePtr(nullptr)
      {}

      Iter& operator++()
      {
        if (nodePtr) {
          nodePtr = nodePtr->next;
        }
        return *this;
      }

      Iter operator++(int)
      {
        Iter copy(*this);
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

      bool operator==(const Iter& rhs) const
      {
        return nodePtr == rhs.nodePtr;
      }

      bool operator!=(const Iter& rhs) const
      {
        return nodePtr != rhs.nodePtr;
      }

     private:
      Node* nodePtr;

      Iter(Node* ptr):
        nodePtr(ptr)
      {}
    };

    struct ConstIter: public std::iterator< std::forward_iterator_tag, T > {
      friend ForwardList;

      ConstIter():
        nodePtr(nullptr)
      {}

      ConstIter(const Iter& fi):
        nodePtr(fi.nodePtr)
      {}

      ConstIter(Iter&& fi):
        nodePtr(fi.nodePtr)
      {}

      ConstIter& operator++()
      {
        if (nodePtr) {
          nodePtr = nodePtr->next;
        }
        return *this;
      }

      ConstIter operator++(int)
      {
        ConstIter copy(*this);
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

      bool operator==(const ConstIter& rhs) const
      {
        return nodePtr == rhs.nodePtr;
      }

      bool operator!=(const ConstIter& rhs) const
      {
        return nodePtr != rhs.nodePtr;
      }

     private:
      const Node* nodePtr;

      ConstIter(const Node* ptr):
        nodePtr(ptr)
      {}
    };

    ForwardList():
      ForwardList(nullptr)
    {}

    ForwardList(const ForwardList& fl):
      ForwardList()
    {
      unsafeInsertAfter(cbeforeBegin(), fl.cbegin(), fl.cend());
    }

    ForwardList(ForwardList&& fl):
      ForwardList(*fl.head())
    {
      *fl.head() = nullptr;
    }

    explicit ForwardList(std::initializer_list< T > il):
      ForwardList()
    {
      unsafeInsertAfter(cbeforeBegin(), il);
    }

    ~ForwardList()
    {
      clear();
      ::operator delete(reinterpret_cast< void* >(preHead_), sizeof(Node));
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

    size_t size() const
    {
      size_t s = 0;
      for (ConstIter i = cbegin(); i != cend(); i++) {
        s++;
      }
      return s;
    }

    void clear()
    {
      while (!empty()) {
        unsafePopFront();
      }
    }

    Iter insertAfter(ConstIter pos, const T& val)
    {
      throwOutsideIter(pos);
      return unsafeInsertAfter(pos, val);
    }

    Iter unsafeInsertAfter(ConstIter pos, const T& val)
    {
      return unsafeInsertAfter(pos, new Node{val, nullptr});
    }

    Iter insertAfter(ConstIter pos, T&& val)
    {
      throwOutsideIter(pos);
      return unsafeInsertAfter(pos, std::move(val));
    }

    Iter unsafeInsertAfter(ConstIter pos, T&& val)
    {
      return unsafeInsertAfter(pos, new Node{std::move(val), nullptr});
    }

    template< typename InputIter >
    Iter insertAfter(ConstIter pos, InputIter first, InputIter last)
    {
      throwOutsideIter(pos);
      return unsafeInsertAfter(pos, first, last);
    }

    template< typename InputIter >
    Iter unsafeInsertAfter(ConstIter pos, InputIter first, InputIter last)
    {
      while (first != last) {
        pos = unsafeInsertAfter(pos, *first);
        ++first;
      }
      return Iter(const_cast< Node* >(pos.nodePtr));
    }

    Iter insertAfter(ConstIter pos, std::initializer_list< T > il)
    {
      throwOutsideIter(pos);
      return unsafeInsertAfter(pos, il);
    }

    Iter unsafeInsertAfter(ConstIter pos, std::initializer_list< T > il)
    {
      return unsafeInsertAfter(pos, il.begin(), il.end());
    }

    template< typename... Args >
    Iter emplaceAfter(ConstIter pos, Args&&... args)
    {
      throwOutsideIter(pos);
      return unsafeInsertAfter(pos, new Node{T(std::forward< Args >(args)...), nullptr});
    }

    template< typename... Args >
    Iter unsafeEmplaceAfter(ConstIter pos, Args&&... args)
    {
      return unsafeInsertAfter(pos, new Node{T(std::forward< Args >(args)...), nullptr});
    }

    Iter eraseAfter(ConstIter pos)
    {
      throwOutsideIter(pos);
      throwOutsideIter(std::next(pos));
      return unsafeEraseAfter(pos);
    }

    Iter unsafeEraseAfter(ConstIter pos)
    {
      Node* posPtr = const_cast< Node* >(pos.nodePtr);
      Node* nextNode = posPtr->next;
      posPtr->next = nextNode->next;
      delete nextNode;
      return Iter(posPtr->next);
    }

    Iter eraseAfter(ConstIter first, ConstIter last)
    {
      throwOutsideIter(first);
      return unsafeEraseAfter(first, last);
    }

    Iter unsafeEraseAfter(ConstIter first, ConstIter last)
    {
      while (first.nodePtr->next != last.nodePtr && first.nodePtr->next) {
        unsafeEraseAfter(first);
      }
      return Iter(const_cast< Node* >(last.nodePtr));
    }

    template< typename... Args >
    T& emplaceFront(Args&&... args)
    {
      pushFront(new Node{T(std::forward< Args >(args)...), nullptr});
    }

    void pushFront(const T& val)
    {
      pushFront(new Node{val, nullptr});
    }

    void pushFront(T&& val)
    {
      pushFront(new Node{std::move(val), nullptr});
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
      throwOutsideIter(pos);
      if (this == std::addressof(fl)) {
        return;
      }
      unsafeSpliceAfter(pos, fl);
    }

    void unsafeSpliceAfter(ConstIter pos, ForwardList& fl)
    {
      Node* next = const_cast< Node* >(pos.nodePtr)->next;
      const_cast< Node* >(pos.nodePtr)->next = *fl.head;
      while (pos.nodePtr->next) {
        ++pos;
      }
      const_cast< Node* >(pos.nodePtr)->next = next;
      *fl.head() = nullptr;
    }

    void spliceAfter(ConstIter pos, ForwardList&& fl)
    {
      throwOutsideIter(pos);
      if (this == std::addressof(fl)) {
        return;
      }
      unsafeSpliceAfter(pos, std::move(fl));
    }

    void unsafeSpliceAfter(ConstIter pos, ForwardList&& fl)
    {
      unsafeSpliceAfter(pos, fl);
    }

    void remove(const T& val)
    {
      struct Equal {
        bool operator()(const T& other) const
        {
          return val_ == other;
        }

       private:
        const T& val_;
      };

      removeIf(Equal{val});
    }

    template< class UnaryPredicate >
    void removeIf(UnaryPredicate check)
    {
      for (ConstIter iter = cbeforeBegin(); iter.nodePtr->next;) {
        if (check(iter.nodePtr->next->data)) {
          eraseAfter(iter);
        } else {
          ++iter;
        }
      }
    }

    void sort()
    {
      return sort(std::less< T >());
    }

    template< typename Compare >
    void sort(Compare comp)
    {
      for (size_t w = 1; w < size(); w *= 2) {
        for (Iter i = beforeBegin(); i.nodePtr->next;) {
          Iter beforeSplit = std::next(i, w);
          if (!beforeSplit.nodePtr || !beforeSplit.nodePtr->next) {
            break;
          }
          Iter beforeEnd = beforeSplit;
          for (size_t subW = w; subW != 0 && beforeEnd.nodePtr->next; --subW) {
            ++beforeEnd;
          }
          i = mergeSorted(i, beforeSplit, beforeEnd, comp);
        }
      }
    }

    void reverse()
    {
      Node* i = *head();
      for (Node* nextPtr = nullptr; i; i = nextPtr) {
        nextPtr = i->next;
        i->next = i;
      }
      *head() = i;
    }

   private:
    Node* preHead_;

    explicit ForwardList(Node* headPtr):
      preHead_(reinterpret_cast< Node* >(::operator new(sizeof(Node))))
    {
      preHead_->next = headPtr;
    }

    Node** head()
    {
      return preHead_ ? std::addressof(preHead_->next) : nullptr;
    }

    const Node* const* head() const
    {
      return preHead_ ? std::addressof(preHead_->next) : nullptr;
    }

    void throwOutsideIter(ConstIter it)
    {
      if (it == cend()) {
        throw std::out_of_range("Invalid attempt to use iterator outside ForwardList");
      }
    }

    Iter unsafeInsertAfter(ConstIter pos, Node* n)
    {
      Node* prevNode = const_cast< Node* >(pos.nodePtr);
      n->next = prevNode->next;
      prevNode->next = n;
      return Iter(n);
    }

    void pushFront(Node* n)
    {
      n->next = (*head())->next;
      (*head())->next = n;
    };

    template< typename Compare >
    Iter mergeSorted(const Iter& bBegin, const Iter& bSplit, const Iter& bEnd, Compare& comp)
    {
      Node* other = bSplit.nodePtr->next;
      Node* endPtr = bEnd.nodePtr->next;
      bSplit.nodePtr->next = endPtr;
      Iter i = bBegin;
      for (; i.nodePtr->next != endPtr; ++i) {
        if (comp(other->data, i.nodePtr->next->data)) {
          std::swap(other, i.nodePtr->next);
        }
      }
      i.nodePtr->next = other;
      while (i.nodePtr->next != endPtr) {
        ++i;
      }
      return i;
    }
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
