#include "PostfixQueue.hpp"

#include <functional>

#include "InfixNode.hpp"
#include "InfixQueue.hpp"
#include "Stack.hpp"

namespace {
  struct PostfixConverter {
    PostfixConverter(odintsov::PostfixQueue& pq):
      expr_(pq)
    {}

    void operator()(const odintsov::InfixNode& node)
    {
      switch (node.getTag()) {
      case odintsov::InfixNode::Tag::OpenParen:
        processOpenParen(node);
        break;
      case odintsov::InfixNode::Tag::CloseParen:
        processCloseParen();
        break;
      case odintsov::InfixNode::Tag::Operator:
        processOperator(node);
        break;
      case odintsov::InfixNode::Tag::Operand:
        processOperand(node);
        break;
      }
    }

    void finalise()
    {
      sendOperatorsOver();
      if (!opers_.empty()) {
        throw std::runtime_error("Syntax error");
      }
    }

   private:
    odintsov::PostfixQueue& expr_;
    odintsov::Stack< odintsov::InfixNode > opers_;

    void processOpenParen(const odintsov::InfixNode& paren)
    {
      opers_.push(paren);
    }

    void processCloseParen()
    {
      sendOperatorsOver();
      if (opers_.empty()) {
        throw std::runtime_error("Parenthesis error");
      }
      odintsov::InfixNode openParen = opers_.tail();
      if (openParen.getTag() != odintsov::InfixNode::Tag::OpenParen) {
        throw std::runtime_error("Parenthesis error");
      }
      opers_.pop();
    }

    void processOperand(const odintsov::InfixNode& operand)
    {
      expr_.push(odintsov::PostfixNode(operand.getOperand()));
    }

    void processOperator(const odintsov::InfixNode& oper)
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
        odintsov::InfixNode oper = opers_.tail();
        if (oper.getTag() != odintsov::InfixNode::Tag::Operator || !confirmSend(oper.getOperator())) {
          break;
        }
        expr_.push(odintsov::PostfixNode(oper.getOperator()));
        opers_.pop();
      }
    }
  };
}

odintsov::PostfixQueue::PostfixQueue(const InfixQueue& iq)
{
  detail::ConstNodeIter< InfixNode > iter = iq.cbegin();
  detail::ConstNodeIter< InfixNode > end = iq.cend();
  PostfixConverter addToConversion(*this);
  while (iter != end) {
    addToConversion(*iter++);
  }
  addToConversion.finalise();
}

long long odintsov::PostfixQueue::solve() const
{
  detail::ConstNodeIter< PostfixNode > iter = cbegin();
  detail::ConstNodeIter< PostfixNode > end = cend();
  Stack< PostfixNode > solver;
  while (iter != end) {
    const PostfixNode node = *iter;
    if (node.getTag() == PostfixNode::Tag::Operator) {
      long long rhs = solver.tail().getOperand();
      solver.pop();
      long long lhs = solver.tail().getOperand();
      solver.pop();
      long long res = node.getOperator().exec(lhs, rhs);
      solver.push(PostfixNode(res));
    } else {
      solver.push(node);
    }
    iter++;
  }
  if (solver.empty()) {
    throw std::runtime_error("Empty expression");
  }
  long long res = solver.tail().getOperand();
  solver.pop();
  if (!solver.empty()) {
    throw std::runtime_error("Syntax error");
  }
  return res;
}
