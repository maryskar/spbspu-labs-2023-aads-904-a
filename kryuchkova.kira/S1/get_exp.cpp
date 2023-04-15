#include "get_exp.h"
#include "queue.h"
#include "stack.h"
#include "utils.h"
#include <string>

namespace kryuchkova
{
  void stringToInfix(std::string & str, Queue < char > & inf)
  {
    size_t string_size = str.size();
    for (size_t i = 0; i < string_size; i++)
    {
      inf.push(str[i]);
    }
  }

  void infixToPostfix(Queue < char > & inf, Queue < char > &post)
  {
    Stack < char > stack_post;
    while (!inf.isEmpty())
    {
      char data = inf.drop();
      if (GetPriority(data) == 4)
      {
        post.push(data);
      }
      else if (GetPriority(data) == 3 || GetPriority(data) == 2)
      {
        stack_post.push(data);
      }
      else if (GetPriority(data) == 1)
      {
        if (data == '(')
        {
          stack_post.push(data);
        }
        else
        {
          char stack_data = stack_post.drop();
          while (stack_data != '(')
          {
            post.push(stack_data);
            stack_data = stack_post.drop();
          }
        }
      }
    }
    while (!stack_post.isEmpty())
    {
      post.push(stack_post.drop());
    }
  }
  long long getResult(Queue < long long > & post);
}