#ifndef SPBSPU_LABS_2023_AADS_904_A_TWOTHREETREEREVERSEITERATOR_H
#define SPBSPU_LABS_2023_AADS_904_A_TWOTHREETREEREVERSEITERATOR_H
#include "twoThreeTree.h"
#include "nodeOfTwoThreeTree.h"
#include "twoThreeTreeIterator.h"
namespace dimkashelk
{
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTree;
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTreeReverseIterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
  {
  friend class TwoThreeTree< Key, Value, Compare >;
  using node_type = details::NodeOfTwoThreeTree< Key, Value, Compare >;
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::pair< Key, Value >;
    using pointer = std::pair< Key, Value >*;
    using reference = std::pair< Key, Value >&;
    TwoThreeTreeReverseIterator &operator++()
    {
      iter_--;
      return *this;
    }
    TwoThreeTreeReverseIterator operator++(int)
    {
      TwoThreeTreeReverseIterator< Key, Value, Compare > result(*this);
      iter_--;
      return result;
    }
    TwoThreeTreeReverseIterator &operator--()
    {
      iter_++;
      return *this;
    }
    TwoThreeTreeReverseIterator operator--(int)
    {
      TwoThreeTreeReverseIterator< Key, Value, Compare > result(*this);
      iter_++;
      return result;
    }
    reference operator*()
    {
      return *iter_;
    }
    pointer operator->()
    {
      return iter_.operator->();
    }
    bool operator==(const TwoThreeTreeReverseIterator &other) const
    {
      return iter_ == other.iter_;
    }
    bool operator!=(const TwoThreeTreeReverseIterator &other) const
    {
      return iter_ != other.iter_;
    }
  private:
    TwoThreeTreeIterator< Key, Value, Compare > iter_;
    TwoThreeTreeReverseIterator(node_type *node, const dimkashelk::TwoThreeTree< Key, Value, Compare > *parent):
      iter_(node, parent)
    {};
  };
}
#endif
