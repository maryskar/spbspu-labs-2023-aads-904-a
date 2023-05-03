#ifndef CONVERTTOPOSTFIXNOTATION_H
#define CONVERTTOPOSTFIXNOTATION_H
#include <fstream>
#include <string>
#include "queue.h"
#include "stack.h"

namespace mashkin
{
  void convertToPostNot(const std::string& line, Stack< std::string >& stc, Queue< std::string >& que);
}
#endif
