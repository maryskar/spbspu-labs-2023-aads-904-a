#include "keysummator.hpp"

#include <utility> 
#include <string>

#include <arithmetic.hpp>

void KeySummator::operator()(const std::pair< const long long, std::string >& key_value)
{
	if (result_ >= 0)
	{
		result_ = hrushchev::sum(result_, key_value.first);
	}
	else
	{
		result_ = hrushchev::sum(key_value.first, result_);
	}
}
