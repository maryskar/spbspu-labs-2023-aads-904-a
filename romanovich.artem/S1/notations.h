#ifndef NOTATIONS_H
#define NOTATIONS_H
#include "queue.h"
namespace romanovich
{
  bool isOperator(const std::string &c);
  bool stackPopCondition(const std::string &q, const std::string &s);
  void getPostfixFromInfix(Queue <std::string> &queue, Stack <std::string> &pStack, Queue <std::string> &pQueue);
  void calcPostfixExpression(Queue <std::string> &postfixQueue, Stack <std::string> &stack, Stack <std::string> &pStack);
  Queue< std::string > splitLine(const std::string &string);
  bool isDigit(const std::string &str);
  std::string doOperation(long long a, long long b, const std::string &oper);
}
#endif
