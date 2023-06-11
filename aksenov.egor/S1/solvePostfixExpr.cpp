#include "solvePostfixExpr.h"
#include <stdexcept>
#include "mathOperations.h"
#include "queue.h"
#include "stack.h"
long long aksenov::solvePostfixExpr(aksenov::Queue< std::string > &queue)
{
  if(queue.isEmpty())
  {
    throw std::invalid_argument("empty queue");
  }
  aksenov::Stack< long long > stack;
  while(!queue.isEmpty())
  {
    std::string elem = queue.drop();
    queue.pop();

  }
}


