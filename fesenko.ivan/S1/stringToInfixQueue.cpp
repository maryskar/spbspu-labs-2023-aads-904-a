#include "stringToInfixQueue.h"

fesenko::Queue< std::string > fesenko::stringToInfixQueue(std::string s)
{
  Queue< std::string > queue;
  std::string element = "";
  size_t i = 0;
  while (i < s.size()) {
    while (i < s.size() && !std::isspace(s[i])) {
      element += s[i];
      i++;
    }
    if (!element.empty()) {
      queue.push(element);
      element = "";
    }
    i++;
  }
  return queue;
}
