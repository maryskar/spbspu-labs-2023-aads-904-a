#include "queue.h"
#include <stdexcept>
namespace
{
  template< typename T >
  T* expand(T *data, size_t old_size, size_t new_size)
  {
    if (new_size <= old_size)
    {
      throw std::logic_error("New size must be greater than old");
    }
    T *new_data = new T[new_size];
    for (size_t i = 0; i < old_size; i++)
    {
      new_data[i] = data[i];
    }
    return new_data;
  }
}
template< typename T>
dimkashelk::Queue<T>::Queue():
  size_(0),
  capacity_(10),
  data_(new T[capacity])
{}
