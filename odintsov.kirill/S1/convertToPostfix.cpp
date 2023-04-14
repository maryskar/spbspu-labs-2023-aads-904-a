#include "convertToPostfix.hpp"

#include <functional>

#include "MathNode.hpp"
#include "Operator.hpp"
#include "Stack.hpp"

struct PostfixConverter {
  void operator()(const odintsov::MathNode& node)
  {
    switch (node.getTag()) {
    case odintsov::MathNode::Tag::OpenParen:
      processOpenParen(node);
      break;
    case odintsov::MathNode::Tag::CloseParen:
      processCloseParen();
      break;
    case odintsov::MathNode::Tag::Operator:
      processOperator(node);
      break;
    case odintsov::MathNode::Tag::Operand:
      processOperand(node);
      break;
    }
  }

  odintsov::Queue< odintsov::MathNode > getQueue()
  {
    sendOperatorsOver();
    if (!opers_.empty()) {
      throw std::runtime_error("Syntax error");
    }
    return expr_;
  }

 private:
  odintsov::Queue< odintsov::MathNode > expr_;
  odintsov::Stack< odintsov::MathNode > opers_;

  void processOpenParen(const odintsov::MathNode& paren)
  {
    opers_.push(paren);
  }

  void processCloseParen()
  {
    sendOperatorsOver();
    if (opers_.empty()) {
      throw std::runtime_error("Parenthesis error");
    }
    odintsov::MathNode openParen = opers_.tail();
    if (openParen.getTag() != odintsov::MathNode::Tag::OpenParen) {
      throw std::runtime_error("Parenthesis error");
    }
    opers_.pop();
  }

  void processOperand(const odintsov::MathNode& operand)
  {
    expr_.push(operand);
  }

  void processOperator(const odintsov::MathNode& oper)
  {
    const odintsov::Operator& operPriority = oper.getOperator();
    sendOperatorsOver([&operPriority](const odintsov::Operator& stackOper) {
      return stackOper >= operPriority;
    });
    opers_.push(oper);
  }

  void sendOperatorsOver()
  {
    sendOperatorsOver([](const odintsov::Operator&) {
      return true;
    });
  }

  void sendOperatorsOver(std::function< bool(const odintsov::Operator&) > confirmSend)
  {
    while (!opers_.empty()) {
      odintsov::MathNode oper = opers_.tail();
      if (oper.getTag() != odintsov::MathNode::Tag::Operator || !confirmSend(oper.getOperator())) {
        break;
      }
      expr_.push(oper);
      opers_.pop();
    }
  }
};

odintsov::Queue< odintsov::MathNode > odintsov::convertToPostfix(const Queue< MathNode >& infixQueue)
{
  detail::ConstNodeIter< MathNode > iter = infixQueue.cbegin();
  detail::ConstNodeIter< MathNode > end = infixQueue.cend();
  PostfixConverter addToConversion;
  while (iter != end) {
    addToConversion(*iter++);
  }
  return addToConversion.getQueue();
}
