#ifndef EXPR_PROCESS_FUNCTIONS_H
#define EXPR_PROCESS_FUNCTIONS_H

namespace skarlygina
{
  bool isSumOverflow(long long, long long);
  bool isMultOverflow(long long, long long);
  bool isDivOverflow(long long, long long);
  long long sum(long long, long long);
  long long substract(long long, long long);
  long long divide(long long, long long);
  long long multiply(long long, long long);
  long long moduloOperation(long long, long long);
  bool isHighPrecedenceOperator(char);
  bool isLowPrecedenceOperator(char);
}

#endif


