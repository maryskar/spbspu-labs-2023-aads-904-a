#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <stdexcept>

namespace detail {
  template< typename T >
  struct Node {
    Node* next;
    T val;
  };

  template< typename T >
  struct ForwardIterator {
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

    T& operator*()
    {
      return nodePtr->data;
    }

    T* operator->()
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
}

namespace odintsov {
  template< typename T >
  class ForwardList {
   public:
    using Iter = detail::ForwardIterator< T >;
    using ConstIter = detail::ForwardIterator< const T >;

    ForwardList():
      head_(nullptr)
    {}

    ForwardList(const ForwardList& fl):
      head_(nullptr)
    {
      unsafeInsertAfter(cbeforeBegin(), fl.cbegin(), fl.cend());
    }

    ForwardList(ForwardList&& fl):
      head_(fl.head_)
    {
      fl.head_ = nullptr;
    }

    ForwardList(std::initializer_list< T > il):
      head_(nullptr)
    {
      unsafeInsertAfter(cbeforeBegin(), il);
    }

    ~ForwardList();

    ForwardList& operator=(const ForwardList& rhs);
    ForwardList& operator=(ForwardList&& rhs);
    ForwardList& operator=(std::initializer_list< T > rhs);

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
      return head_->data;
    }

    const T& unsafeFront() const
    {
      return head_->data;
    }

    Iter beforeBegin()
    {
      return Iter(reinterpret_cast< detail::Node< T >* >(std::addressof(head_)));
    }

    ConstIter cbeforeBegin() const
    {
      return ConstIter(reinterpret_cast< detail::Node< const T >* >(std::addressof(head_)));
    }

    Iter begin()
    {
      return Iter(head_);
    }

    ConstIter cbegin() const
    {
      return ConstIter(head_);
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
      return !head_;
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
      return unsafeInsertAfter(pos, new detail::Node< T >{nullptr, val});
    }

    Iter insertAfter(ConstIter pos, T&& val)
    {
      assertIterInside(pos);
      return unsafeInsertAfter(pos, val);
    }

    Iter unsafeInsertAfter(ConstIter pos, T&& val)
    {
      return unsafeInsertAfter(pos, new detail::Node< T >{nullptr, val});
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
      Iter lastInserted(pos.nodePtr);
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
      unsafeInsertAfter(pos, new detail::Node< T >{nullptr, T(std::forward< Args >(args)...)});
    }

    template< class... Args >
    Iter unsafeEmplaceAfter(ConstIter pos, Args&&... args)
    {
      unsafeInsertAfter(pos, new detail::Node< T >{nullptr, T(std::forward< Args >(args)...)});
    }

    Iter eraseAfter(ConstIter pos)
    {
      assertIterInside(pos);
      return unsafeEraseAfter(pos);
    }

    Iter unsafeEraseAfter(ConstIter pos)
    {
      detail::Node< T >* nextNode = pos.nodePtr->next;
      pos.nodePtr->next = nextNode->next;
      delete nextNode;
      return Iter(pos.nodePtr->next);
    }

    Iter eraseAfter(ConstIter first, ConstIter last)
    {
      assertIterInside(first);
      const ConstIter end = cend();
      for (ConstIter next = std::next(first); next != last; ++next) {
        if (next == end) {
          throw std::invalid_argument("ForwardList erase range failed, iterator to last elem incorrect");
        }
      }
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
      pushFront(new detail::Node< T >{nullptr, T(std::forward< Args >(args)...)});
    }

    void pushFront(const T& val)
    {
      pushFront(new detail::Node< T >{nullptr, val});
    }

    void pushFront(T&& val)
    {
      pushFront(new detail::Node< T >{nullptr, val});
    }

    void popFront()
    {
      if (!head_) {
        throw std::logic_error("Attempt to pop empty ForwardList");
      }
      unsafePopFront();
    }

    void unsafePopFront()
    {
      detail::Node< T >* next = head_->next;
      delete head_;
      head_ = next;
    }

    void merge(ForwardList& fl);
    void merge(ForwardList&& fl);
    void spliceAfter(ConstIter pos, ForwardList& fl);
    void spliceAfter(ConstIter pos, ForwardList&& fl);
    void remove(const T& val);
    template< class UnaryPredicate >
    void removeIf(UnaryPredicate c);
    void reverse();

   private:
    detail::Node< T >* head_;

    void assertIterInside(ConstIter it)
    {
      if (it == cend()) {
        throw std::range_error("Invalid attempt to use iterator outside ForwardList");
      }
    }

    Iter unsafeInsertAfter(ConstIter pos, detail::Node< T >* n)
    {
      detail::Node< T >* prevNode = pos.nodePtr;
      n->next = prevNode->next;
      prevNode->next = n->next;
      return Iter(n);
    }

    void pushFront(detail::Node< T >* n)
    {
      n->next = head_;
      head_ = n;
    };
  };
}

#endif
