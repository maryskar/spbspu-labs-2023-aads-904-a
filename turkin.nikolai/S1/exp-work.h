#ifndef EXP_WORK
#define EXP_WORK

#include <string>
#include <queue.h>
#include "data-type.h"

void str2Inf(std::string & dirt, Queue< calc_t > & input);
void inf2Post(Queue< calc_t > & input, Queue < calc_t > & output);
long long post2Result(Queue< calc_t > & output);

#endif
