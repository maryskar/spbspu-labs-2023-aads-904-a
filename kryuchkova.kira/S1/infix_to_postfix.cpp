#include "infix_to_postfix.h"
#include "stack.h"
#include "queue.h"
#include "part_of_exp.h"

namespace kryuchkova
{
  Queue< ExpressionMember > GetPostfixExp(Queue< ExpressionMember > & inf)
  {
    Queue< ExpressionMember > post;
    Stack< ExpressionMember > stack;
    while (!inf.isEmpty())
    {
      ExpressionMember data = inf.drop();
      if (data.isOperand())
      {
        post.push(data);
      }
      else if (data.isParenthesis())
      {
        if (data.getParenthesis() == parenthesis_t::OPEN)
        {
          stack.push(data);
        }
        else if (data.getParenthesis() == parenthesis_t::CLOSE)
        {
          ExpressionMember temp = stack.drop();
          while (!stack.isEmpty() && !temp.isParenthesis())
          {
            post.push(temp);
            temp = stack.drop();
          }
          if (stack.isEmpty())
          {
            throw std::invalid_argument("Check your expression");
          }
        }
        else
        {
          if (stack.isEmpty())
          {
            stack.push(data);
          }
          else
          {

          }
        }
      }
    }
  }
}
