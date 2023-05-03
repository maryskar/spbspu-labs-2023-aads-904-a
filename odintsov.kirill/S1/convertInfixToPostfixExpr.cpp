#include "convertInfixToPostfixExpr.hpp"

#include "InfixNode.hpp"
#include "PostfixNode.hpp"
#include "Queue.hpp"
#include "Stack.hpp"

odintsov::Queue< odintsov::PostfixNode > odintsov::convertInfixToPostfixExpr(Queue< InfixNode > expr)
{
  Queue< PostfixNode > res;
  Stack< InfixNode > opers;
  while (!expr.empty()) {
    InfixNode curNode = expr.head();
    expr.pop();
    if (curNode.isOpenParen()) {
      opers.push(curNode);
    } else if (curNode.isCloseParen()) {
      while (!opers.empty()) {
        InfixNode oper = opers.tail();
        if (!oper.isOperator()) {
          break;
        }
        res.push(PostfixNode(oper.getOperator()));
        opers.pop();
      }
      if (opers.empty()) {
        throw std::runtime_error("Parenthesis error");
      }
      InfixNode openParen = opers.tail();
      if (!openParen.isOpenParen()) {
        throw std::runtime_error("Parenthesis error");
      }
      opers.pop();
    } else if (curNode.isOperator()) {
      const Operator& curOper = curNode.getOperator();
      while (!opers.empty()) {
        InfixNode oper = opers.tail();
        if (!oper.isOperator() || oper.getOperator() < curOper) {
          break;
        }
        res.push(PostfixNode(oper.getOperator()));
        opers.pop();
      }
      opers.push(curNode);
    } else {
      res.push(PostfixNode(curNode.getOperand()));
    }
  }
  while (!opers.empty()) {
    InfixNode oper = opers.tail();
    if (!oper.isOperator()) {
      break;
    }
    res.push(PostfixNode(oper.getOperator()));
    opers.pop();
  }
  if (!opers.empty()) {
    throw std::runtime_error("Syntax error");
  }
  return res;
}
