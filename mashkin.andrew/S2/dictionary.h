#ifndef S2_DICTIONARY_H
#define S2_DICTIONARY_H

namespace mashkin
{
  template< class Key, class Value, class Compare >
  class Dictionary
  {
  public:
    void push(Key k, Value v);
    Value get(Key k);
    Value drop(Key k);
  };
}
#endif
