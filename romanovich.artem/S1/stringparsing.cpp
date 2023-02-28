#include "stringparsing.h"
#include "queue.h"
void splitLine(const std::string &string)
{
  Queue< char > queue = Queue< char >();
  for (char c: string)
  {
    if (c != ' ')
    {
      queue.push(c);
    }
  }
}