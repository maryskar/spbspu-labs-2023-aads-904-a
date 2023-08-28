#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "forward_list.h"
#include "forward_list_const_iterator.h"
#include "forward_list_iterator.h"

namespace kryuchkova
{
  template< typename T >
  class ForwardList;
  template< typename T >
  class ConstForwardIterator;
  template< typename T >
  class ForwardList;

  template< typename Key, typename Value, typename Compare = std::less< > >
  class Dictionary 
  {
  public:
    using key_type = Key;
    using val = value;
    using this_t = Dictionary< Key, Value, Compare >;
    using val_type = std::pair< const Key, Value >;
    using iterator = ForwardIterator< T >;
    using const_iterator = ConstForwardIterator< T >;

    Dictionary();
    Dictionary(const this_t & other);
    Dictionary(this_t && other);
    explicit Dictionary(const Compare & comp);
    Dictionary(std::initializer_list< val_type > init, const Compare & comp = Compare());
    ~Dictionary() = default;

    this_t & operator=(const this_t & other);
    this_t & operator=(this_t && other);
    this_t & operator=(std::initializer_list< val_type > init);
    val & operator[](const key_type & key);
    val & operator[](key_type && key);



    void push(Key k, Value v);
    Value get(Key k);
    Value drop(Key k);

  };
}

#endif
