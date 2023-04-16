#include <limits>
#include <stdexcept>
#include <string>
#include "queue.h"

namespace kryuchkova
{

  long long maximum = std::numeric_limits< long long >::max();
  long long minimum = std::numeric_limits< long long >::min();

  void isOverflow(long long data)
  {
    if (data > maximum || data < minimum)
    {
      throw std::overflow_error("Overflow");
    }
  }

  void incorrectString(Queue < std::string > & inf)
  {
    Queue < std::string > queue = inf;
    
  }

}
