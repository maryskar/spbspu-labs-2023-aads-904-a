#ifndef GETINPUTSTREAM_H
#define GETINPUTSTREAM_H

#include <istream>

namespace potapova
{
  std::istream& getInputStream(const int argc, const char* const* const argv);
}

#endif
