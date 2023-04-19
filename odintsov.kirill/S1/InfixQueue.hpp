#ifndef INFIXQUEUE_HPP
#define INFIXQUEUE_HPP

#include "InfixNode.hpp"
#include "Queue.hpp"

namespace odintsov {
  class InfixQueue: public Queue< InfixNode > {
   public:
    InfixQueue(const std::string& str);
    long long solve() const;
  };
}

#endif
