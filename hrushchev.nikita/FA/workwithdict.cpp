#include "workwithdict.hpp"
#include <string>
#include <avltree.hpp>
#include "commands.hpp"
#include "queue.hpp"

hrushchev::Commands::Commands()
{
	dict1_.insert("infix", addToInfixDict);
	dict2_.insert("postfix", addToPostfixDict);
	dict3_.insert("sum_postfix", sumPostfix);
	dict3_.insert("subtract_postfix", subtractPostfix);
	dict3_.insert("multiply_postfix", multiplyPostfix);
	dict3_.insert("division_postfix", divisionPostfix);
}