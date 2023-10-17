#ifndef ARITHMEXPRESSIONMEMBER_H
#define ARITHMEXPRESSIONMEMBER_H

#include <cstdint>
#include "queue.h"

namespace potapova
{
  class ArithmExpMember;
  using expr_queue = Queue< ArithmExpMember >;

  class ArithmExpMember
  {
    public:
      enum class Type:
        std::uint8_t
      {
        Num,
        Operation
      };

      ArithmExpMember();

      explicit ArithmExpMember(long long num);
      explicit ArithmExpMember(char operation);
      ArithmExpMember& operator=(long long num);
      ArithmExpMember& operator=(char operation);
      long long getNum();
      char getOperation();
      Type getType();
    private:
      union
      {
        long long num_;
        char operation_;
      };

      Type type_;
  };
}

#endif
