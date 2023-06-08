#ifndef EXP_WORK_HPP
#define EXP_WORK_HPP

#include <string>
#include <queue.hpp>
#include "data-type.hpp"

using pinf_t = turkin::calc_t< turkin::PINF >;
using pfix_t = turkin::calc_t< turkin::PFIX >;

namespace turkin
{
  Queue< pinf_t > str2Inf(std::string & dirt);
  Queue< pfix_t > inf2Post(Queue< pinf_t > & input);
  long long post2Result(Queue< pfix_t > & output);
};

#endif
