#ifndef CONVERTTOPOSTFIXNOTATION_H
#define CONVERTTOPOSTFIXNOTATION_H
#include <fstream>
#include <string>
#include "queue.h"
#include "stack.h"

namespace mashkin
{
  Queue< std::string > convertToPostfixNotation(std::istream& inp, Stack< std::string >& stc, Queue< std::string >& que);
}
#endif
