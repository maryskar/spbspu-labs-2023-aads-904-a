#ifndef NOTATION_H
#define NOTATION_H
#include <iostream>
#include <fstream>
#include "queue.h"
#include "stack.h"

int getPostfix(Queue< char >& res, std::istream& inStream, std::ostream& errStream);

#endif
