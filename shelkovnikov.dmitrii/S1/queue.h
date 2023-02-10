#ifndef SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#define SPBSPU_LABS_2023_AADS_904_A_QUEUE_H
#include <cstddef>
#include <stdexcept>
#include "expand.h"
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
    ~Queue()
    {
      delete[] data_;
    }
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
      T element = data_[0];
      for (size_t i = 0; i < size_ - 1; i++)
      {
        data_[i] = data_[i + 1];
      }
      size_--;
      return element;
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
