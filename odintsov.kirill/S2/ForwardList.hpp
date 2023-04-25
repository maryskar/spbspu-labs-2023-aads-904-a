#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <utility>

namespace detail {
  template< typename T >
  struct Node {
    T val;
    Node* next;
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
    ForwardList();

    ForwardList(const ForwardList& fl);
    ForwardList(ForwardList&& fl);
    ForwardList(std::initializer_list< T > il);
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

    Iter beforeBegin();
    ConstIter cbeforeBegin() const;
    Iter begin();
    ConstIter cbegin() const;
    Iter end();
    ConstIter cend() const;

    bool empty() const
    {
      return !head_;
    }

    void clear();

    Iter insertAfter(ConstIter pos, const T& val)
    {
      assertIterInside(pos);
      return unsafeInsertAfter(pos, val);
    }

    Iter unsafeInsertAfter(ConstIter pos, const T& val)
    {
      return unsafeInsertAfter(pos, new detail::Node< T >{val, nullptr});
    }

    Iter insertAfter(ConstIter pos, T&& val)
    {
      assertIterInside(pos);
      return unsafeInsertAfter(pos, val);
    }

    Iter unsafeInsertAfter(ConstIter pos, T&& val)
    {
      return unsafeInsertAfter(pos, new detail::Node< T >{val, nullptr});
    }

    template< class... Args >
    Iter emplaceAfter(ConstIter pos, Args&&... args)
    {
      assertIterInside(pos);
      unsafeInsertAfter(pos, new detail::Node< T >{T(std::forward< Args >(args)...), nullptr});
    }

    template< class... Args >
    Iter unsafeEmplaceAfter(ConstIter pos, Args&&... args)
    {
      unsafeInsertAfter(pos, new detail::Node< T >{T(std::forward< Args >(args)...), nullptr});
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
      pushFront(new detail::Node< T >{T(std::forward< Args >(args)...), nullptr});
    }

    void pushFront(const T& val)
    {
      pushFront(new detail::Node< T >{val, nullptr});
    }

    void pushFront(T&& val)
    {
      pushFront(new detail::Node< T >{val, nullptr});
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
