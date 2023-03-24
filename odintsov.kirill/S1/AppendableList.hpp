#ifndef APPENDABLELIST_HPP
#define APPENDABLELIST_HPP

namespace odintsov {
  template< typename T >
  class AppendableList {
    public:
      AppendableList();
      ~AppendableList();

      void push(const T& data);
      void pop();
      virtual void unsafePop() = 0;

    protected:
      struct Node {
          T data;
          Node* next;
      };

      Node* head_;
      Node* tail_;
  };
}
#endif
