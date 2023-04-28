#include "convertstringtoinfix.hpp"
#include <string>
#include <cstring>
#include <sstream>
#include "queue.hpp"

namespace hr = hrushchev;

hr::Queue< std::string > hr::convertStringToInfix(std::string str)
{
  hr::Queue< std::string > infix_queue;
  std::stringstream string_stream(str);
  std::string token;
  while (string_stream >> token)
  {
    infix_queue.push(token);
  }
  return infix_queue;
}

