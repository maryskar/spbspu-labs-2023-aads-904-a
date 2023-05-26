#ifndef STACK_H
#define STACK_H
#include <stdexcept>

#include "list.h"

template < typename T >
class Stack {
private:
  List< T >* top_;

public:
  Stack():
    top_(nullptr)
  {}

  T top() const {
    if (empty()) {
      throw std::runtime_error("Stack is empty.");
    }
    return top_->data;
  }

  Stack(const Stack< T >& other):
    top_(nullptr)
  {
    if (!other.empty()) {
      List< T >* tp = other.top_;
      while (tp != nullptr) {
        push(tp->data);
        tp = tp->next;
      }
    }
  }

  Stack& operator=(const Stack< T >& other) {
    if (this != &other) {
      Stack tp(other);
      std::swap(top_, tp.top_);
    }
    return *this;
  }

  Stack& operator=(Stack< T >&& other) {
    if (this != &other) {
      clear();
      top_ = other.top_;
      other.top_ = nullptr;
    }
    return *this;
  }

  Stack(Stack< T >&& other):
    top_(other.top_)
  {
    other.top_ = nullptr;
  }

  ~Stack() {
    clear();
  }

  void push(const T& rhs) {
    List< T >* newNode = new List< T >{rhs, top_};
    top_ = newNode;
  }

  T drop() {
    if (top_ == nullptr) {
      throw std::out_of_range("Stack is empty");
    }
    T value = top_->data;
    List< T >* top = top_;
    top_ = top_->next;
    delete top;
    return value;
  }

  bool empty() const {
    return top_ == nullptr;
  }

  size_t size() const {
    List< T >* node = top_;
    size_t count = 0;
    while (node != nullptr) {
      node = node->next;
      count++;
    }
    return count;
  }

  void clear() {
    while (!empty()) {
      drop();
    }
    top_ = nullptr;
  }
};

#endif
