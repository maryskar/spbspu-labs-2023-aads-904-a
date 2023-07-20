#include <iostream>
#include <fstream>
#include "valueType.h"
#include "queue.h"
#include "inputInfixQueue.h"
#include "divideExpression.h"

int main()
{
  potapova::expr_queue infix_expr;
  if (!inputInfixQueue(infix_expr))
  {
    std::cerr << "Input error\n";
    return 1;
  }
  potapova::expr_queue postfix_queue(potapova::composePostfixQueue(infix_expr));
  while (!postfix_queue.empty())
  {
    if (postfix_queue.front().type == potapova::ArithmExpMember::Type::Num)
    {
      std::cout << postfix_queue.front().num << ' ';
    }
    else
    {
      std::cout << postfix_queue.front().operation << ' ';
    }
    postfix_queue.pop();
  }
  return 0; 
}
