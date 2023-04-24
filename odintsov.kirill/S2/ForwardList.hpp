#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <stdexcept>

namespace detail {
  template< typename T >
  struct Node {
    T val;
    Node* next;
  };

  template< typename T >
  struct ForwardIterator {
    ForwardIterator():
      nodePtr_(nullptr)
    {}

    ForwardIterator(Node< T >* ptr):
      nodePtr_(ptr)
    {}

    ForwardIterator& operator++()
    {
      if (nodePtr_) {
        nodePtr_ = nodePtr_->next;
      }
      return *this;
    }

    ForwardIterator operator++(int)
    {
      ForwardIterator< T > copy(*this);
      if (nodePtr_) {
        nodePtr_ = nodePtr_->next;
      }
      return copy;
    }

    T& operator*()
    {
      return nodePtr_->data;
    }

    T* operator->()
    {
      return std::addressof(nodePtr_->data);
    }

    bool operator==(const ForwardIterator& rhs) const
    {
      return nodePtr_ == rhs.nodePtr_;
    }

    bool operator!=(const ForwardIterator& rhs) const
    {
      return nodePtr_ != rhs.nodePtr_;
    }

   private:
    Node< T >* nodePtr_;
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
      if (!head_) {
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

   private:
    detail::Node< T > head_;
  };
}

#endif
