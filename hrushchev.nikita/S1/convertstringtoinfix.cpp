#include "convertstringtoinfix.hpp"
#include <string>
#include <queue.hpp>

hrushchev::Queue<std::string> hrushchev::convertStringToInfix(std::string str)
{
  namespace hrn = hrushchev;
  hrn::Queue< std::string > infix_queue;

  std::string delimiter = " ";
  size_t pos = 0;
  std::string token;

  while ((pos = str.find(delimiter)) != std::string::npos)
  {
    token = str.substr(0, pos);
    infix_queue.push(token);
    str.erase(0, pos + 1);
  }

  infix_queue.push(str);

  return infix_queue;
}

