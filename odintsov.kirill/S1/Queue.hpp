#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace odintsov {
  template< typename T >
  class Queue {
   public:
    Queue();
    ~Queue();

    T& head();
    const T& head() const;
    void push(const T& data);
    void pop();
    bool empty() const;

   private:
    struct Node {
      T data;
      Node* next;
    };

    Node* head_;
    Node* tail_;
  };
}

#endif
