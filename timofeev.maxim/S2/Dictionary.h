#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "ForwardList.h"
namespace timofeev
{
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class Dictionary
  {
  public:
    using iter = ForwardListIterator< std::pair< Key, Value > >;
    using constIter = ForwardListConstIterator< std::pair< Key, Value > >;

    void push(Key k, Value v);
    Value get(Key k);
    Value drop(Key k);

    Dictionary();
    ~Dictionary() = default;

    bool empty() const noexcept;
    size_t size() const noexcept;

    void clear();

  private:
    ForwardList< std::pair< Key, Value > > data_;
    Compare compare_;
    size_t size_;
  };

  template< typename Key, typename Value, typename Compare >
  Dictionary< Key, Value, Compare >::Dictionary():
    data_(),
    compare_(),
    size_()
  {}

  template< typename Key, typename Value, typename Compare >


}

#endif //S2_DICTIONARY_H
