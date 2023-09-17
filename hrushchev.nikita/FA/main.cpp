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
  hrn::AVLTree< std::string, std::string > dict_with_vars;
  hrn::set(dict_with_vars, "pi", "3.1415");

  hrn::addToInfixDict(dict_with_infix, "1", "sin(pi)");
  hrn::addToPostfixDict(dict_with_postfix, dict_with_infix, dict_with_vars, "p1", "1", 7);
  hrn::calculate(dict_with_postfix, "p1", std::cout);
  printInfix(dict_with_infix, std::cout);
  printPostfix(dict_with_postfix, std::cout);
}
