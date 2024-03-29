#include "get_result.h"
#include "queue.h"
#include "stack.h"
#include "part_of_exp.h"
#include "calculate.h"

namespace kryuchkova
{
  long long getResult(Queue< ExpressionMember > &post)
  {
    Stack < long long > result;
    while (!post.isEmpty())
    {
      ExpressionMember data = post.getFront();
      post.pop();
      if (data.isOperand())
      {
        result.push(data.getOperand());
      }
      else
      {
        long long rhs = result.getTop();
        result.pop();
        long long lhs = result.getTop();
        result.pop();
        if (data.getOperation() == operation_t::ADDITION)
        {
          result.push(calcSum(lhs, rhs));
        }
        else if (data.getOperation() == operation_t::SUBTRACTION)
        {
          result.push(calcDiff(lhs, rhs));
        }
        else if (data.getOperation() == operation_t::MULTIPLICATION)
        {
          result.push(calcMulti(lhs, rhs));
        }
        else if (data.getOperation() == operation_t::DIVISION)
        {
          result.push(calcDiv(lhs, rhs));
        }
        else if (data.getOperation() == operation_t::EUCLIDEAN_DIVISION)
        {
          result.push(calcEucDiv(lhs, rhs));
        }
        else
        {
          throw std::invalid_argument("Bad operation");
        }
      }
      if (result.isEmpty())
      {
        throw std::invalid_argument("Check expression");
      }
    }
    long long data = result.getTop();
    result.pop();
    return data;
  }
}
