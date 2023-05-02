#ifndef EXP_WORK_HPP
#define EXP_WORK_HPP

#include <string>
#include <queue.hpp>
#include "data-type.hpp"

using pinf_t = turkin::datatype::calc_t< turkin::datatype::PINF >;
using pfix_t = turkin::datatype::calc_t< turkin::datatype::PFIX >;

turkin::Queue< pinf_t > str2Inf(std::string & dirt);
turkin::Queue< pfix_t > inf2Post(turkin::Queue< pinf_t > & input);
long long post2Result(turkin::Queue< pfix_t > & output);

#endif
