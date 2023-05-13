#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include "ForwardIterator.hpp"

namespace odintsov {
  namespace detail {
    template< typename T, typename Compare >
    ForwardIterator< T > mergeSorted(const ForwardIterator< T >& bBegin, const ForwardIterator< T >& bSplit,
        const ForwardIterator< T >& bEnd, Compare& comp)
    {
      typename ForwardIterator< T >::Node* other = bSplit.nodePtr->next;
      typename ForwardIterator< T >::Node* endPtr = bEnd.nodePtr->next;
      bSplit.nodePtr->next = endPtr;
      ForwardIterator< T > i = bBegin;
      for (; i.nodePtr->next != endPtr; ++i) {
        if (comp(other->val, i.nodePtr->next->val)) {
          std::swap(other, i.nodePtr->next);
        }
      }
      i.nodePtr->next = other;
      while (i.nodePtr->next != endPtr) {
        ++i;
      }
      return i;
    }
  }

  template< typename T, typename Compare >
  void mergeSort(detail::ForwardIterator< T > beforeBegin, Compare& comp)
  {
    detail::ConstForwardIterator< T > sizeIter = beforeBegin;
    size_t size = 0;
    while ((++sizeIter).nodePtr) {
      ++size;
    }
    for (size_t w = 1; w < size; w *= 2) {
      for (detail::ForwardIterator< T > i = beforeBegin; i.nodePtr->next;) {
        detail::ForwardIterator< T > beforeSplit = std::next(i, w);
        if (!beforeSplit.nodePtr || !beforeSplit.nodePtr->next) {
          break;
        }
        detail::ForwardIterator< T > beforeEnd = beforeSplit;
        for (size_t subW = w; subW != 0 && beforeEnd.nodePtr->next; --subW) {
          ++beforeEnd;
        }
        i = detail::mergeSorted(i, beforeSplit, beforeEnd, comp);
      }
    }
  }
}

#endif
