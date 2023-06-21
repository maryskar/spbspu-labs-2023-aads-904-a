#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include "forward-list.hpp"

namespace turkin
{
  template< typename Key, typename Value, typename Compare >
  class Dictionary
  {
    public:
      Dictionary() = default;
      Dictionary(const Dictionary< Key, Value, Compare > & rhs);
      Dictionary(Dictionary< Key, Value, Compare > && rhs);
      Dictionary & operator=(const Dictionary< Key, Value, Compare > & rhs);
      Dictionary & operator=(Dictionary< Key, Value, Compare > && rhs);
      ~Dictionary() = default;
      void push(Key k, Value v);
      Value & get(Key k);
      const Value & get(Key k) const;
      Value & drop(Key k);
      const Value & drop(Key k) const;
    private:
      ForwardList< Value > fl_;
  };
}

#endif
