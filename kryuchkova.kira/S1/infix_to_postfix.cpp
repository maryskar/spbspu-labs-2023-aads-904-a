#include "infix_to_postfix.h"
#include "stack.h"
#include "queue.h"
#include "part_of_exp.h"

namespace kryuchkova
{
  Queue< ExpressionMember > getPostfixExp(Queue< ExpressionMember > & inf)
  {
    Queue< ExpressionMember > post;
    Stack< ExpressionMember > stack;
    while (!inf.isEmpty())
    {
      ExpressionMember data = inf.drop();
      inf.pop();
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
          stack.pop();
          while (!temp.isParenthesis())
          {
            post.push(temp);
            if (stack.isEmpty())
            {
              throw std::invalid_argument("Check your expression");
            }
            temp = stack.drop();
            stack.pop();
          }
        }
      }
      else
      {
        if (!stack.isEmpty())
        {
          ExpressionMember temp = stack.drop();
          stack.pop();
          while (!stack.isEmpty() && !cmpPriority(temp.getOperation(), data.getOperation()) && !temp.isParenthesis())
          {
            post.push(temp);
            temp = stack.drop();
            stack.pop();
          }
          if (!temp.isParenthesis())
          {
            post.push(temp);
          }
          else
          {
            stack.push(temp);
          }
        }
        stack.push(data);
      }
    }
    while (!stack.isEmpty())
    {
      post.push(stack.drop());
      stack.pop();
    }
    return post;
  }
}
