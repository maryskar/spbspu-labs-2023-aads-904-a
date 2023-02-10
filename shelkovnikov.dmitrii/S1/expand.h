#ifndef SPBSPU_LABS_2023_AADS_904_A_EXPAND_H
#define SPBSPU_LABS_2023_AADS_904_A_EXPAND_H
#include <cstddef>
#include <stdexcept>
namespace dimkashelk
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
#endif
