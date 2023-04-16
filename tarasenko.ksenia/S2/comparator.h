#ifndef COMPARATOR_H
#define COMPARATOR_H
namespace tarasenko
{
  template< typename Key, typename Value>
  struct Comparator
  {
    bool operator()(const details::Pair< Key, Value >& right_k, const details::Pair< Key, Value >& left_k)
    {
      return right_k.key_ < left_k.key_;
    }
  };
}
#endif
