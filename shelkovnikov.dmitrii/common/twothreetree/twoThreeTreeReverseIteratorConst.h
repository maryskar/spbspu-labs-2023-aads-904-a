#ifndef SPBSPU_LABS_2023_AADS_904_A_TWOTHREETREEREVERSEITERATORCONST_H
#define SPBSPU_LABS_2023_AADS_904_A_TWOTHREETREEREVERSEITERATORCONST_H
#include "twoThreeTree.h"
#include "nodeOfTwoThreeTree.h"
#include "twoThreeTreeIteratorConst.h"
namespace dimkashelk
{
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTree;
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTreeIteratorConst;
  template< typename Key, typename Value, typename Compare >
  class TwoThreeTreeReverseIteratorConst: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > >
  {
  friend class TwoThreeTree< const Key, Value, Compare >;
  friend class TwoThreeTreeIteratorConst< const Key, Value, Compare >;
  using node_type = details::NodeOfTwoThreeTree< const Key, Value >;
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = const std::pair< const Key, Value >;
    using pointer = const std::pair< const Key, Value >*;
    using reference = const std::pair< const Key, Value >&;
    TwoThreeTreeReverseIteratorConst &operator++()
    {
      iter_--;
      return *this;
    }
    TwoThreeTreeReverseIteratorConst operator++(int)
    {
      TwoThreeTreeReverseIterator< const Key, Value, Compare > result(*this);
      iter_--;
      return result;
    }
    TwoThreeTreeReverseIteratorConst &operator--()
    {
      iter_++;
      return *this;
    }
    TwoThreeTreeReverseIteratorConst operator--(int)
    {
      TwoThreeTreeReverseIterator< const Key, Value, Compare > result(*this);
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
    bool operator==(const TwoThreeTreeReverseIteratorConst &other) const
    {
      return iter_ == other.iter_;
    }
    bool operator!=(const TwoThreeTreeReverseIteratorConst &other) const
    {
      return iter_ != other.iter_;
    }
  private:
    TwoThreeTreeIteratorConst< Key, Value, Compare > iter_;
    TwoThreeTreeReverseIteratorConst(node_type *node, const dimkashelk::TwoThreeTree< const Key, Value, Compare > *parent):
      iter_(node, parent)
    {};
  };
}
#endif
