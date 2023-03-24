#ifndef CONVERTTOPOSTFIXNOTATION_H
#define CONVERTTOPOSTFIXNOTATION_H
#include <fstream>
#include <string>
#include "queue.h"
#include "stack.h"

namespace mashkin
{
  void convertToPostfixNotation(std::ifstream& inpFile, Stack< std::string >& stc, Queue< std::string >& que);
}
#endif
