#ifndef SPBSPU_LABS_2023_AADS_904_A_STACK_H
#define SPBSPU_LABS_2023_AADS_904_A_STACK_H
#include <cstddef>
#include <stdexcept>
#include "expand.h"
namespace dimkashelk
{
  template < typename T >
  class Stack
  {
  public:
    Stack():
      size_(0),
      capacity_(10),
      data_(new T[capacity_])
    {}
    ~Stack()
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
      size_--;
      return data_[size_];
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
