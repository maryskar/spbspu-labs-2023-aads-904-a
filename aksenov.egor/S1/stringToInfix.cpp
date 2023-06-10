#include "stringToInfix.h"
#include "queue.h"
#include <stdexcept>

aksenov::Queue< std::string > aksenov::convertToInfix(std::string line)
{
  if (line.empty())
  {
    throw std::invalid_argument("empty string");
  }
  std::string delimetr = " ";
  aksenov::Queue< std::string > infQueue;
  while (line.length())
  {
    size_t space = line.find_first_of(delimetr);
    if (space == line.npos) {
      infQueue.push(line.substr(0));
      line.clear();
    } else {
      infQueue.push(line.substr(0, space));
      line = line.substr(space + 1);
    }
  }
  return infQueue;
}
