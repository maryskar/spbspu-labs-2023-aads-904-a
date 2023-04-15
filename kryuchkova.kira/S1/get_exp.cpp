#include "get_exp.h"
#include "queue.h"
#include "stack.h"
#include <string>

namespace kryuchkova
{
  void stringToInfix(std::string & str, Queue < long long > & inf);
  void infixToPostfix(Queue < long long > & inf, Queue < long long > &post);
  long long getResult(Queue < long long > & post);
}