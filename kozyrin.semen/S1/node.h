#ifndef NODE_H
#define NODE_H

namespace kozyrin {
  template< typename T >
  struct node_t {
    T value_;
    node_t< T >* next_ = nullptr;
  };

  template< typename T >
  node_t< T >* copy(const node_t< T >* src)
  {
    if (!src->next_) {
      return new node_t< T >{src->value_};
    }
    return new node_t< T >{src->value_, copy(src->next_)};
  }
}

#endif
