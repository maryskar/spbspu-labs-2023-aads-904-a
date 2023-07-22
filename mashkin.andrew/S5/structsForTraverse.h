#ifndef MASHKIN_ANDREW_STRUCTSFORTRAVERSE_H
#define MASHKIN_ANDREW_STRUCTSFORTRAVERSE_H
#include <utility>
#include <string>
#include <queue.h>

namespace mashkin
{
  struct QueueForTraverse
  {
    void operator()(const std::pair< const int, std::string >& key_value);
    mashkin::Queue< std::string > res_;
  };
}
#endif
