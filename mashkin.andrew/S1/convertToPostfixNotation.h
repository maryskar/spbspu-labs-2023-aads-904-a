#ifndef CONVERTTOPOSTFIXNOTATION_H
#define CONVERTTOPOSTFIXNOTATION_H
#include <fstream>
#include <string>
#include "queue.h"
#include "stack.h"

namespace mashkin
{
  void convertToPostNot(const std::string& line, Queue< std::string >& que);
}
#endif
