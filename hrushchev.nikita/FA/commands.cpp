#include "commands.hpp"
#include <string>
#include <avltree.hpp>
#include <queue.hpp>
#include "convertstringtoinfix.hpp"

void hrushchev::addToInfixDict(AVLTree< std::string, Queue< std::string > >& dict,
		const std::string& name,
		const std::string& expr)
{
  Queue< std::string > infix_queue(convertStringToInfix(expr));
  dict.insert(name, infix_queue);
}
