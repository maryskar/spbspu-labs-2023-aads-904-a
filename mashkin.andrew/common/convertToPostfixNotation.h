#ifndef CONVERTTOPOSTFIXNOTATION_H
#define CONVERTTOPOSTFIXNOTATION_H
#include "queue.h"
#include "stack.h"
#include <fstream>
#include <string>

namespace mashkin
{
  void convertToPostNot(const std::string& line, Queue< std::string >& que);
}
#endif
