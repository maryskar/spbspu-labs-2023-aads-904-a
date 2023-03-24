#ifndef APPENDABLELIST_HPP
#define APPENDABLELIST_HPP

namespace odintsov {
  template< typename T >
  class AppendableList {
    public:
      AppendableList(const T& data);
      ~AppendableList();

      void push(const T& data);

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
