#ifndef EXP_WORK_H
#define EXP_WORK_H

#include <string>
#include <queue.h>
#include "data-type.h"

void str2Inf(std::string & dirt, Queue< calc_t > & input);
void inf2Post(Queue< calc_t > & input, Queue < calc_t > & output);
long long post2Result(Queue< calc_t > & output);

#endif
