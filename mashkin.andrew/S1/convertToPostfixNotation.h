#ifndef S1_CONVERTTOPOSTFIXNOTATION_H
#define S1_CONVERTTOPOSTFIXNOTATION_H
#include <fstream>
#include "stack.h"
#include "queue.h"

void convertToPostfixNotation(std::ifstream& inpFile, Stack< char >& stc, Queue< char >& que);
#endif
