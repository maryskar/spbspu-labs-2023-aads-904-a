#ifndef FORWARDLISTCONSTITERATOR_H
#define FORWARDLISTCONSTITERATOR_H

#include <memory>
#include "forwardList.h"

namespace potapova
{
  template< typename T >
  class ForwardListConstIterator
  {
    public:
      ForwardListConstIterator(): node(nullptr)
      {

      }

      ~ForwardListConstIterator() = default;
      ForwardListConstIterator(const ForwardListConstIterator&) = default;
      ForwardListConstIterator& operator=(const ForwardListConstIterator&) = default;

      const ForwardListConstIterator& operator++() const
      {
        assert(node != nullptr);
        node = node->next;
        return *this;
      }

      ForwardListConstIterator operator++(int) const
      {
        assert(node != nullptr);
        ForwardListConstIterator result(*this);
        ++(*this);
        return result;
      }

      const T& operator*() const
      {
        assert(node != nullptr);
        return node->data;
      }

      const T* operator->() const
      {
        assert(node != nullptr);
        return std::addressof(node->data);
      }

      bool operator!=(const ForwardListConstIterator& rhs) const
      {
        return !(rhs == *this);
      }

      bool operator==(const ForwardListConstIterator& rhs) const
      {
        return node == rhs.node;
      }
    private:
      const ForwardList< T >* node;
  };
}

#endif
