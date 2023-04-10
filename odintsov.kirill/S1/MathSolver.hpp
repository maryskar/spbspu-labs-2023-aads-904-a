#ifndef MATHSOLVER_HPP
#define MATHSOLVER_HPP

#include <functional>

#include "Operator.hpp"
#include "Queue.hpp"
#include "Stack.hpp"

namespace odintsov {
  struct MathSolver {
    void operator()(const std::string& node);

    long long getResult();

   private:
    class MathNode {
     public:
      enum class Tag {
        Operand,
        Operator,
        Paren
      };

      MathNode(long long operand);
      MathNode(const std::string& str);
      ~MathNode();

      bool isDataType(Tag tag) const;

      long long getOperand() const;
      Operator& getOperator();
      const Operator& getOperator() const;
      char getParen() const;

     private:
      Tag tag_;

      union Data {
        long long operand;
        Operator oper;
        char paren;
      } data_;
    };

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
