#ifndef APPENDABLELIST_HPP
#define APPENDABLELIST_HPP

namespace odintsov {
  template < typename T >
  class AppendableList {
    public:
      void push(const T& rhs);

    private:
      struct Node {
          T data;
          Node* next;
      };

      Node head_;
  };
}
#endif
