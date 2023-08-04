#include "copyconstructor.h"

namespace chulkov {
  template< typename T >
  void copyList(List< T >*& dest, const List< T >* src) {
    dest = nullptr;
    List< T >* prev = nullptr;
    while (src != nullptr) {
      List< T >* node = new List< T >{src->data, nullptr};
      if (dest == nullptr) {
        dest = node;
      } else {
        prev->next = node;
      }
      prev = node;
      src = src->next;
    }
  }
}
