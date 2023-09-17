#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <avltree.hpp>
#include "convertstringtoinfix.hpp"
#include "convertinfixtopostfix.hpp"
#include "calcucalepostfix.hpp"
#include "commands.hpp"
#include "queue.hpp"
#include "stack.hpp"

int main()
{
  namespace hrn = hrushchev;
  hrn::AVLTree< std::string, hrn::Queue< std::string > > dict_with_infix;
  hrn::AVLTree< std::string, std::pair< hrn::Queue< std::string >, int > > dict_with_postfix;
  hrn::addToInfixDict(dict_with_infix, "1", "5");
  hrn::addToInfixDict(dict_with_infix, "2", "3");
  hrn::addToPostfixDict(dict_with_postfix, dict_with_infix, "p1", "1", 4);
  hrn::addToPostfixDict(dict_with_postfix, dict_with_infix, "p2", "2", 4);
  hrn::sumPostfix(dict_with_postfix, "res", "p1", "p2", 5);
  hrn::calculate(dict_with_postfix, "res", std::cout);
}
