#ifndef FORWARD_LIST_ITERATOR_H
#define FORWARD_LIST_ITERATOR_H
#include <iterator>
#include "node.h"

namespace kryuchkova
{
  template < typename T >
  class ForwardList;

  template < typename T >
  class ForwardIterator: public std::iterator< std::forward_iterator_tag, T >
  {
    public:
      using this_t = ForwardIterator< T >;
      friend class ForwardList< T >;

      ForwardListIterator():
        node_(nullptr)
      {}
      explicit ForwardIterator(Node< T > * node):
        node_(node)
      {}
      ForwardIterator(const this_t&) = default;
      ~ForwardIterator() = default;

      this_t& operator=(const this_t&) = default;
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
