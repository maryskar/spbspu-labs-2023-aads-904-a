#ifndef MATHSOLVER_HPP
#define MATHSOLVER_HPP

#include <functional>

#include "MathNode.hpp"
#include "Queue.hpp"
#include "Stack.hpp"

namespace odintsov {
  struct MathSolver {
    void operator()(MathNode& node);

    long long getResult();

   private:
    Stack< MathNode > opers_;
    Queue< MathNode > result_;

    void processParen(MathNode& paren);
    void processOperand(MathNode& operand);
    void processOperator(MathNode& oper);
    void sendOperatorsOver();

    void sendOperatorsOver(std::function< bool(const Operator&) > confirmSend);
  };
}

#endif
