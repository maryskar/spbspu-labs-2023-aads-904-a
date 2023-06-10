#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include "list.h"
namespace aksenov{
  template< typename T >
  class Queue
  {
    public:
      explicit Queue();
      ~Queue();
      void pust(const T &val);
      void pop();
      T drop();
      bool isEmpty() const;
    private:
      aksenov::List< T > *front_;
      aksenov::List< T > *tail_;
  };
}
#endif
