#include "operator.h"

#include <iomanip>
#include <limits>

auto defineOperator(char op)
{
	if (op == '+')
	{
		return plus;
	}
	else if (op == '-')
	{
		return minus;
	}
	else if (op == '*')
	{
		return multiple;
	}
	else if (op == '/')
	{
		return division;
	}
	else if (op == '%')
	{
		return mod;
	}
	else
	{
		throw std::logic_error("unknown operator");
	}
}


Operator::Operator(char op) :
	mathOperator(defineOperator(op)),
	priority(definePriority(op))
{

}
