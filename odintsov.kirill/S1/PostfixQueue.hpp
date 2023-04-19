#ifndef POSTFIXQUEUE_HPP
#define POSTFIXQUEUE_HPP

#include "InfixQueue.hpp"
#include "PostfixNode.hpp"
#include "Queue.hpp"

namespace odintsov {
  class PostfixQueue: public Queue< PostfixNode > {
   public:
    PostfixQueue(const InfixQueue& iq);
    long long solve() const;
  };
}

#endif
