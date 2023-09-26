#include "workwithdict.hpp"
#include "commands.hpp"

hrushchev::Commands::Commands()
{
	dict1_.insert("print", printDict);
	dict2_.insert("complement", complementDict);
	dict2_.insert("intersect", intersectDict);
	dict2_.insert("union", unionDict);
}