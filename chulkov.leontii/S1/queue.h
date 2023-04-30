#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>

template < typename T >
class Queue {
private:
  struct Node {
    T value;
    Node* next;

    Node(const T& val, Node* nxt = nullptr):
      value(val),
      next(nxt)
    {}
  };

  Node* front_;
  Node* back_;
  size_t size_;

public:
  Queue():
    front_(nullptr),
    back_(nullptr),
    size_(0)
  {}

  ~Queue()
  {
    while (!empty()) {
      pop();
    }
  }

  void push(T&& rhs)
  {
    Node* node = new Node(std::move(rhs));
    if (empty()) {
      front_ = back_ = node;
    } else {
      back_->next = node;
      back_ = node;
    }
    ++size_;
  }

  T drop()
  {
    if (empty()) {
      throw std::out_of_range("Queue is empty");
    }
    T value = front_->value;
    Node* node = front_;
    front_ = front_->next;
    if (front_ == nullptr) {
      back_ = nullptr;
    }
    delete node;
    --size_;
    return value;
  }

  const T& drop() const
  {
    if (empty()) {
      throw std::out_of_range("Queue is empty");
    }
    return front_->value;
  }

  bool empty() const
  {
    return size_ == 0;
  }

  void pop()
  {
    drop();
  }

  size_t size() const
  {
    return size_;
  }
};

#endif
