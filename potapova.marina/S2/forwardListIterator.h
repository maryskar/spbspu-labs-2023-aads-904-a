#ifndef FORWARDLISTITERATOR_H
#define FORWARDLISTITERATOR_H

#include <memory>
#include "forwardList.h"

namespace potapova
{
  template< typename T >
  class ForwardListIterator
  {
    public:
      ForwardListIterator(): node(nullptr)
      {

      }

      ~ForwardListIterator() = default;
      ForwardListIterator(const ForwardListIterator&) = default;
      ForwardListIterator& operator=(const ForwardListIterator&) = default;

      ForwardListIterator& operator++()
      {
        assert(node != nullptr);
        node = node->next;
      }

      ForwardListIterator operator++(int)
      {
        assert(node != nullptr);
        ForwardListIterator result(*this);
        ++(*this);
        return result;
      }

      T& operator*()
      {
        assert(node != nullptr);
        return node->data;
      }

      T* operator->()
      {
        assert(node != nullptr);
        return std::addressof(node->data);
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

      bool operator!=(const ForwardListIterator& rhs) const
      {
        return !(rhs == *this);
      }

      bool operator==(const ForwardListIterator& rhs) const
      {
        return node == rhs.node;
      }
    private:
      ForwardList< T >* node;
  };
}

#endif
