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

  void infixToPostfix(Queue < char > & inf, Queue < long long > &post)
  {
    Stack < char > stack_post;
    while (!inf.isEmpty())
      {
        char data = inf.drop();
        int priority = GetPriority(data);
      }
  }
  long long getResult(Queue < long long > & post);
}