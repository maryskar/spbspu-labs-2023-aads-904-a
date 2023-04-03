#include "convertinfixtopostfix.hpp"
#include <string>
#include "queue.hpp"
#include "stack.hpp"

Queue< std::string > convertInfixToPostfix(Queue< std::string >& infixQueue)
{
  Queue< std::string > postfixQueue;
  Stack< std::string > s;
  while (!infixQueue.isEmpty())
  {
    std::string token = infixQueue.get();
    infixQueue.pop();
    if (isdigit(token[0]))
    {
      postfixQueue.push(token);
    } 
    else if (token == "+" || token == "-")
    {
      while (!s.isEmpty() && (s.get() == "+" || s.get() == "-" || s.get() == "*" || s.get() == "/"))
      {
        postfixQueue.push(s.get());
        s.pop();
      }
      s.push(token);
    } 
    else if (token == "*" || token == "/")
    {
      while (!s.isEmpty() && (s.get() == "*" || s.get() == "/"))
      {
        postfixQueue.push(s.get());
        s.pop();
      }
      s.push(token);
    }
    else if (token == "(")
    {
      s.push(token);
    }
    else if (token == ")")
    {
      while (!s.isEmpty() && s.get() != "(")
      {
        postfixQueue.push(s.get());
        s.pop();
      }
      s.pop();
    } 
    else 
    {
      std::logic_error("Ivalid token");
    }
  }
  while (!s.isEmpty())
  {
    postfixQueue.push(s.get());
    s.pop();
  }
  return postfixQueue;
}
