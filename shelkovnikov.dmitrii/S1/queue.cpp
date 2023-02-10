#include "queue.h"
template< typename T>
dimkashelk::Queue<T>::Queue():
  size_(0),
  capacity_(10),
  data_(new T[capacity])
{}