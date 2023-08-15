#ifndef FORWARD_LIST_CONST_ITERATOR_H
#define FORWARD_LIST_CONST_ITERATOR_H
#include <iterator>
#include "node.h"

namespace kryuchkova
{
  template < typename T >
  class ForwardList;
  template < typename T >
  class ForwardIteraator;

  template < typename T >
  class ConstForwardIterator: public std::iterator< std::forward_iterator_tag, const T >
  {
    public:
      using this_t = ConstForwardIterator< T >;
      friend class ForwardList< T >;
      friend class ForwardIterator< T >;

      ConstForwardIterator():
        node_(nullptr)
      {}
      explicit ConstForwardIterator(Node< T > * node):
        node_(node)
      {}
      ConstForwardIterator(const ForwardIteraator< T >& temp):
        node_(temp.node_)
      {}
      ConstForwardIterator(const this_t&) = default;
      ~ConstForwardIterator() = default;

      this_t& operator=(const this_t&) = default;
      this_t& operator=(const ForwardIterator< T >& temp)
      {
        node_ = temp.node_;
        return *this;
      }
      this_t& operator++()
      {
        if (node_ != nullptr)
        {
          node_ = node_->next;
        }
        return *this;
      }
      this_t operator++(int)
      {
        if (node_ != nullptr)
        {
          this_t temp(*this);
          ++(*this);
          return temp;
        }
      }
      bool operator!=(const this_t& rhs) const
      {
        return !(node_ == rhs.node_);
      }
      bool operator==(const this_t& rhs) const
      {
        return node_ == rhs.node_;
      }

    private:
      Node< T > * node_;
  };
}

#endif
