#ifndef DICTIONARY_H
#define DICTIONARY_H

template < typename Key, typename Value, typename Compare >
class Dictionary
{
public:
  Iterator< std::pair< Key, Value > > begin();
  ConstIterator< std::pair< Key, Value > > begin() const;
  Iterator< std::pair< Key, Value > > end();
  ConstIterator< std::pair< Key, Value > > end() const;
  ConstIterator< std::pair< Key, Value > > cbegin() const;
  ConstIterator< std::pair< Key, Value > > cend() const;

  void push(Key k, Value v);
  Value get(Key k);
  Value drop(Key k);
};

#endif
