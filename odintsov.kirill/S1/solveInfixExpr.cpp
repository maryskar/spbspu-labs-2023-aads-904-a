#include "solveInfixExpr.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

#include <StringSplitter.hpp>

#include "PostfixNode.hpp"
#include "convertInfixToPostfixExpr.hpp"
#include "solvePostfixExpr.hpp"

long long odintsov::solveInfixExpr(Queue< InfixNode > expr)
{
  Queue< PostfixNode > postExpr = convertInfixToPostfixExpr(expr);
  return solvePostfixExpr(postExpr);
}

long long odintsov::solveInfixExpr(const std::string& exprStr)
{
  Queue< InfixNode > expr;
  StringSplitter split(exprStr);
  while (!split.empty()) {
    std::string nodeStr;
    split >> nodeStr;
    try {
      expr.push(InfixNode(std::stoll(nodeStr)));
    } catch (...) {
      if (nodeStr.size() != 1) {
        throw std::logic_error("Incorrect operand or operator");
      }
      char nodeChr = nodeStr[0];
      expr.push(InfixNode(nodeChr));
    }
  }
  return solveInfixExpr(expr);
}
