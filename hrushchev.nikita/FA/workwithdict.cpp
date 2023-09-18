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
	dict4_.insert("print_infix", printInfix);
	dict5_.insert("print_postfix", printPostfix);
	dict6_.insert("help", help);
	dict7_.insert("calculate", calculate);
	dict8_.insert("set", set);
	dict9_.insert("variable", printVariable);
	dict10_.insert("variables", printVariables);
}