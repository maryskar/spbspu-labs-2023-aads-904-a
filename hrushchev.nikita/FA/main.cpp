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
  hrn::addToInfixDict(dict_with_infix, "first", "123+123-sin(1)");
  hrn::addToPostfixDict(dict_with_postfix, dict_with_infix, "second", "first", 4);
  hrn::calculate(dict_with_postfix, "second", std::cout);
}
