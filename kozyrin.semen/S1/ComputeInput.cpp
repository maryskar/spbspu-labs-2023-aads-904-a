#include "ComputeInput.h"

int compute(std::istream& inStream, std::ostream& outStream, std::ostream& errStream)
{
  Queue< char > queue = Queue< char >();
  while (!inStream.eof()) {
    if (!getPostfix(queue, inStream, errStream)) {
      return 1;
    }
    Stack< char > stack = Stack< char >();

    while (!queue.isEmpty()) {
      char chr = queue.drop();
      if
    }
  }
}