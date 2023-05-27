#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>

#include "list.h"

namespace chulkov {
  template < typename T >
  class Queue {
  private:
    List< T >* front_;
    List< T >* back_;
    size_t size_;

  public:
    Queue():
      front_(nullptr),
      back_(nullptr),
      size_(0)
    {}

    Queue(const Queue< T >& other):
      front_(nullptr),
      back_(nullptr),
      size_(0)
    {
      if (!other.empty()) {
        List< T >* tp = other.front_;
        while (tp != nullptr) {
          push(tp->data);
          tp = tp->next;
        }
      }
    }

    Queue(Queue< T >&& other):
      front_(other.front_),
      back_(other.back_)
    {
      other.front_ = nullptr;
      other.back_ = nullptr;
    }

    Queue& operator=(const Queue< T >& other) {
      if (this != &other) {
        Queue temp(other);
        std::swap(front_, temp.front_);
        std::swap(back_, temp.back_);
      }
      return *this;
    }

    Queue& operator=(Queue< T >&& other) {
      if (this != &other) {
        clear();
        front_ = other.front_;
        back_ = other.back_;
        other.front_ = nullptr;
        other.back_ = nullptr;
      }
      return *this;
    }

    ~Queue() {
      while (!empty()) {
        clear();
      }
    }

    void push(const T& rhs) {
      List< T >* node = new List< T >{rhs, nullptr};
      if (empty()) {
        front_ = back_ = node;
      } else {
        if (back_ == nullptr) {
          throw std::runtime_error("pointer is null");
        }
        back_->next = node;
        back_ = node;
      }
      ++size_;
    }

    T drop() {
      if (empty()) {
        throw std::out_of_range("Queue is empty");
      }
      T value = front_->data;
      List< T >* node = front_;
      front_ = front_->next;
      if (front_ == nullptr) {
        back_ = nullptr;
      }
      delete node;
      --size_;
      return value;
    }

    const T& drop() const {
      if (empty()) {
        throw std::out_of_range("Queue is empty");
      }
      return front_->data;
    }

    bool empty() const {
      return size_ == 0;
    }

    size_t size() const {
      return size_;
    }

    void clear() {
      while (!empty()) {
        drop();
      }
    }
  };
}

#endif
