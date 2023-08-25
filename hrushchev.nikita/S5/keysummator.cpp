#include "keysummator.hpp"

#include <utility> 
#include <string>

#include <arithmetic.hpp>

void KeySummator::operator()(const std::pair< const long long, std::string >& key_value)
{
	hrushchev::sum(result_,key_value.first);
}
