#ifndef DICTIONARY_H
#define DICTIONARY_H

namespace tarasenko
{
  template< typename Key, typename Value, typename Compare >
  class Dictionary
  {
  public:
   void push(Key& k, Value& v);
   Value get(Key& k);
   Value drop(Key& k); // !!!
   //...
   //Value find(Key& k);
   //void remove(Key& k);
  private:
   ForwardList <Pair> list;
  };

  template< typename Key, typename Value, typename Compare >
  void Dictionary< Key, Value, Compare >::push(Key& k, Value& v)
  {

  };
  template< typename Key, typename Value, typename Compare >
  Value Dictionary< Key, Value, Compare >::get(Key& k)
  {

  };
  template< typename Key, typename Value, typename Compare >
  Value Dictionary< Key, Value, Compare >::drop(Key& k)
  {

  };
}

#endif
