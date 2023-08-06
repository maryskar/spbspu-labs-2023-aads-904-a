#ifndef AVLITERATOR
#define AVLITERATOR
#include "AVL.h"

namespace fesenko
{
  template< typename Key, typename Value, typename Compare >
  class AVL;

  template< typename Key, typename Value, typename Compare >
  class AVLIterator
  {
    friend class AVL< Key, Value, Compare >;
   public:
    using this_t = AVLIterator;
    AVLIterator();
    AVLIterator(const this_t &) = default;
    explicit AVLIterator(tree *);
    ~AVLIterator() = default;
    this_t &operator=(const this_t &) = default;
    this_t &operator++();
    this_t operator++(int);
    this_t &operator--();
    this_t operator--(int);
    T &operator*();
    const T &operator*() const;
    T *operator->();
    const T *operator->() const;
    bool operator!=(const this_t &) const;
    bool operator==(const this_t &) const;
   private:
    tree *fake_;
    tree *node_;
    Compare comp_;
  };
}
#endif
