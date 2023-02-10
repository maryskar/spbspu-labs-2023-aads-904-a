#ifndef SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#define SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#include <cstddef>
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
namespace dimkashelk
{
  template < typename T >
  class Queue
  {
  public:
    Queue():
      size_(0),
      capacity_(10),
      data_(new T[capacity_])
    {}
    void push(T rhs)
    {
      if (size_ == capacity_)
      {
        T *new_data = expand< T >(data_, size_, capacity_ + 10);
        delete[] data_;
        data_ = new_data;
        capacity_ += 10;
      }
      data_[size_++] = rhs;
    }
    T drop()
    {
      size_--;
      return data_[size_ + 1];
    }
    bool empty()
    {
      return size_ == 0;
    }
  private:
    size_t size_;
    size_t capacity_;
    T *data_;
  };
}
#endif
