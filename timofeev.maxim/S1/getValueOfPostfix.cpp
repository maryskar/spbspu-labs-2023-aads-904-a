#include "getValueOfPostfix.h"
#include <stdexcept>
#include <string>
#include "queue.h"
#include "stack.h"
namespace timofeev
{
  long long getValueOfPostfix(Queue< std::string >& postfix)
  {
    if (postfix.isEmpty())
    {
      throw std::invalid_argument("No postfix");
    }
    Stack< std::string > result;
    while (!postfix.isEmpty())
    {
      std::string c = postfix.drop();
      postfix.pop();
      try
      {
        std::stoll(c);
        result.push(c);
      }
      catch (const std::invalid_argument &)
      {
        long long int first = std::stoll(result.drop());
        result.pop();
        long long int second = std::stoll(result.drop());
        result.pop();
        switch (c[0])
        {
          case '+':
            result.push(std::to_string(second + first));
            break;
          case '-':
            result.push(std::to_string(second - first));
            break;
          case '*':
            result.push(std::to_string(second * first));
            break;
          case '/':
            result.push(std::to_string(second / first));
            break;
          case '%':
            result.push(std::to_string(second % first));
            break;
          default:
            throw std::runtime_error("unknown operator");
        }
      }
    }
    long long res = std::stoll(result.drop());
    result.pop();
    if (!result.isEmpty())
    {
      throw std::runtime_error("invalid postfix ups");
    }
    return res;
  }
}