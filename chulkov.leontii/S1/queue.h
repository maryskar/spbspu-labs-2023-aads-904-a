#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include "list.h"

namespace chulkov {
  template < typename T >
  class Queue
  {
  public:
    Queue():
      front_(nullptr),
      back_(nullptr)
    {}

    Queue(const Queue< T >& other):
      front_(nullptr),
      back_(nullptr)
    {
      try {
        if (!other.empty()) {
          List< T >* tp = other.front_;
          while (tp != nullptr) {
            push(tp->data);
            tp = tp->next;
          }
        }
      } catch (...) {
        clear();
        front_ = nullptr;
        back_ = nullptr;
        throw;
      }
    }

    Queue(Queue< T >&& other):
      front_(other.front_),
      back_(other.back_)
    {
      other.front_ = nullptr;
      other.back_ = nullptr;
    }

    Queue& operator=(const Queue< T >& other)
    {
      if (this != std::addressof(other)) {
        Queue temp(other);
        std::swap(front_, temp.front_);
        std::swap(back_, temp.back_);
      }
      return *this;
    }

    Queue& operator=(Queue< T >&& other)
    {
      if (this != std::addressof(other)) {
        clear();
        front_ = other.front_;
        back_ = other.back_;
        other.front_ = nullptr;
        other.back_ = nullptr;
      }
      return *this;
    }

    ~Queue()
    {
      clear();
    }

    void push(const T& rhs)
    {
      List< T >* node = new List< T >{rhs, nullptr};
      if (empty()) {
        front_ = back_ = node;
      } else {
        back_->next = node;
        back_ = node;
      }
    }

    void drop()
    {
      if (empty()) {
        throw std::out_of_range("Queue is empty");
      }
      List< T >* temp = front_;
      if (front_ == back_) {
        back_ = nullptr;
        front_ = nullptr;
      } else {
        front_ = front_->next;
      }
      delete temp;
    }

    T& getTop()
    {
      return const_cast< T& >(static_cast< const Queue& >(*this).getTop());
    }

    const T& getTop() const
    {
      if (empty()) {
        throw std::out_of_range("Queue is empty");
      }
      return front_->data;
    }

    bool empty() const
    {
      return front_ == nullptr;
    }

    void clear()
    {
      List< T >* node = front_;
      while (node != nullptr) {
        List< T >* next = node->next;
        delete node;
        node = next;
      }
      front_ = back_ = nullptr;
    }
  private:
    List< T >* front_;
    List< T >* back_;
  };
}

#endif
