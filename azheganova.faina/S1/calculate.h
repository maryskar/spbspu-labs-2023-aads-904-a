#ifndef CALCULATE_H
#define CALCULATE_H
#include "queue.h"

namespace azheganova
{
  long long summarize(long long secondnum, long long firstnum);
  long long subtract(long long secondnum, long long firstnum);
  long long multiply(long long secondnum, long long firstnum);
  long long divide(long long secondnum, long long firstnum);
  long long calculateRemainder(long long secondnum, long long firstnum);
  long long calculatePostfix(azheganova::Queue< std::string > & postfix);
}

#endif
