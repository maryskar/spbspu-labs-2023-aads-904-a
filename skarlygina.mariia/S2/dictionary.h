#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "iterator.h"
#include "citerator.h"
#include "forwardlist.h"

namespace skarlygina
{
  template < typename Key, typename Value, typename Compare >
  class Dictionary
  {
  public:
    Iterator< std::pair< Key, Value > > begin();
    Iterator< std::pair< Key, Value > > end();
    CIterator< std::pair< Key, Value > > begin() const;
    CIterator< std::pair< Key, Value > > end() const;
    CIterator< std::pair< Key, Value > > cbegin() const;
    CIterator< std::pair< Key, Value > > cend() const;

    Iterator< std::pair< Key, Value > > find(const Key&);
    CIterator< std::pair< Key, Value > > cfind(const Key&) const;

    void push(const Key&, const Value&);
    const Value& get(const Key&) const;
    void pop(const Key&);
    void clear();
    bool is_empty() const noexcept;
  private:
    ForwardList< std::pair< Key, Value > > list_;
  };
}
#endif
