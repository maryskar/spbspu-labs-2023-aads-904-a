#ifndef BOX_H
#define BOX_H

namespace bowlstalls {
  template< typename T >
  struct box_t {
    T value_ = 0;
    box_t< T >* prev_ = nullptr;
    box_t< T >* next_ = nullptr;
  };
}

#endif
