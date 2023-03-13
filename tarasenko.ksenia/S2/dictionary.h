#ifndef DICTIONARY_H
#define DICTIONARY_H

template< typename Key, typename Value, typename Compare >
class Dictionary
{
public:
 void push(Key k, Value v);
 Value get(Key k);
 Value drop(Key k);
//...
};

#endif
