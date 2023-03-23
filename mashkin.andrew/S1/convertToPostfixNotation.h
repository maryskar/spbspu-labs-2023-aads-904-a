#ifndef CONVERTTOPOSTFIXNOTATION_H
#define CONVERTTOPOSTFIXNOTATION_H
#include <fstream>
#include "queue.h"
#include "stack.h"

namespace mashkin
{
  void convertToPostfixNotation(std::ifstream& inpFile, Stack< char >& stc, Queue< char >& que);
}
#endif
