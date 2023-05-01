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
          if (stack.isEmpty())
          {
            throw std::invalid_argument("Check your expression");
          }
          ExpressionMember temp = stack.drop();
          while (!stack.isEmpty() && !temp.isParenthesis())
          {
            post.push(temp);
            if (stack.isEmpty())
            {
              throw std::invalid_argument("Check your expression");
            }
            temp = stack.drop();
          }
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
          ExpressionMember temp = stack.drop();
          if (cmpPriority(temp.getOperation(), data.getOperation()))
          {
            stack.push(temp);
            stack.push(data);
          }
          else
          {
            ExpressionMember temp = stack.drop();
            while (!cmpPriority(temp.getOperation(), data.getOperation()))
            {
              post.push(temp);
              if (stack.isEmpty())
              {
                break;
              }
              temp = stack.drop();
            }
            stack.push(data);
          }
        }
      }
    }
    while (!stack.isEmpty())
    {
      post.push(stack.drop());
    }
    return post;
  }
}
