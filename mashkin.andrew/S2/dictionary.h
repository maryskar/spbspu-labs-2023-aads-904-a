#ifndef S2_DICTIONARY_H
#define S2_DICTIONARY_H
#include <utility>
#include "forwardConstIterator.h"
#include "forwardIterator.h"
#include "forwardList.h"

namespace mashkin
{
  template< class Key, class Value, class Compare >
  class Dictionary
  {
  public:
    using key_type = Key;
    using value_type = std::pair< const Key, Value >;
    using iter = Iterator< Value >;
    using const_iter = ConstIterator< Value >;

    Dictionary();
    Dictionary(const Compare& comp);
    template< class InputIt >
    Dictionary(InputIt first, InputIt last, const Compare& comp);
    Dictionary(const Dictionary& other);
    Dictionary(Dictionary&& other);

    void push(Key k, Value v);
    Value get(Key k);
    void drop(Key k);

  private:
    ForwardList< value_type > pair_;
    Compare comp_;
  };

  template< class Key, class Value, class Compare >
  Dictionary< Key, Value, Compare >::Dictionary():
    pair_()
  {
  }

  template< class Key, class Value, class Compare >
  Dictionary< Key, Value, Compare >::Dictionary(const Compare& comp):
    pair_()
  {
  }

  template< class Key, class Value, class Compare >
  template< class InputIt >
  Dictionary< Key, Value, Compare >::Dictionary(InputIt first, InputIt last, const Compare& comp)
  {
  }

  template< class Key, class Value, class Compare >
  void Dictionary< Key, Value, Compare >::push(Key k, Value v)
  {
    std::pair< Key, Value > pair{k, v};
    pair_.push_front(pair);
  }
}
#endif
