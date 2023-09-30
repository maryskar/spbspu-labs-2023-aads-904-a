#ifndef MASHKIN_ANDREW_STRUCTSFORTRAVERSE_H
#define MASHKIN_ANDREW_STRUCTSFORTRAVERSE_H
#include <string>
#include <utility>
#include "queue.h"
#include "stack.h"

namespace mashkin
{
  struct QueueForTraverse
  {
    void operator()(const std::pair< const int, std::string >& key_value);
    int summ_ = 0;
    mashkin::Queue< std::string > res_;
  };

  struct StackForTraverse
  {
    void operator()(const std::pair< const int, std::string >& key_value);
    int summ_ = 0;
    mashkin::Stack< std::string > res_;
  };
}
#endif
