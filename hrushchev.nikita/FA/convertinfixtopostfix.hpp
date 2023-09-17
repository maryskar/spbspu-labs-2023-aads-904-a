#ifndef CONVERINFIXTOPOSTFIX_HPP
#define CONVERINFIXTOPOSTFIX_HPP
#include <string>
#include <avltree.hpp>
#include "queue.hpp"

namespace hrushchev
{
  Queue< std::string > convertInfixToPostfix(Queue< std::string >& infixQueue,
    AVLTree< std::string, std::string >& variables);
}

#endif

