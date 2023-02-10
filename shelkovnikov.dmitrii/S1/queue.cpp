#include "queue.h"
template< typename T>
dimkashelk::Queue<T>::Queue():
  size(0),
  capacity(10),
  data_(new T[capacity])
{}