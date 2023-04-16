#include "get_exp.h"
#include "queue.h"
#include "stack.h"
#include "utils.h"
#include <string>

namespace kryuchkova
{
  void stringToInfix(std::string & str, Queue < std::string > & inf)
  {
    int begin = 0;
    int end = str.find(' ');
    int count = 0;
    while (end > -1)
    {
      count = end - begin;
      inf.push(str.substr(begin, count));
      begin = end + 1;
      end = str.find(' ', begin);
    }
    count = end - begin;
    inf.push(str.substr(begin, count));
  }

  void infixToPostfix(Queue < std::string > & inf, Queue < std::string > &post)
  {
    Stack < std::string > stack_post;
    while (!inf.isEmpty())
    {
      std::string data = inf.drop();
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
        if (data[0] == '(')
        {
          stack_post.push(data);
        }
        else
        {
          std::string stack_data = stack_post.drop();
          while (stack_data[0] != '(')
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

  long long getResult(Queue < std::string > & post)
  {
    Stack < long long > operands;
    while (!post.isEmpty())
    {
      std::string data = post.drop();
      if (GetPriority(data) == 4)
      {
        operands.push(std::stoll(data));
      }
      else
      {
        long long second = operands.drop();
        long long first = operands.drop();
        operands.push(calculate(first, second, data));
      }
    }
    return operands.drop();
  }
}
