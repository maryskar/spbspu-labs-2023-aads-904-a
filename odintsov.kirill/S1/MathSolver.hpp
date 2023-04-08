#ifndef MATHSOLVER_HPP
#define MATHSOLVER_HPP

#include "MathNode.hpp"
#include "Queue.hpp"
#include "Stack.hpp"

namespace odintsov {
  struct MathSolver {
    void operator()(odintsov::MathNode& node);

    long long getResult();

   private:
    odintsov::Stack< odintsov::MathNode > opers_;
    odintsov::Queue< odintsov::MathNode > result_;

    void processParen(odintsov::MathNode& paren);
    void processOperand(odintsov::MathNode& operand);
    void processOperator(odintsov::MathNode& oper);
    void sendOperatorsOver();

    template< typename F >
    void sendOperatorsOver(F confirmSend);
  };
}

#endif
