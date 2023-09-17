#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <utility>
#include <ostream>
#include <avltree.hpp>
#include "queue.hpp"

namespace hrushchev
{
  using infix_dict = AVLTree< std::string, Queue< std::string > >;
  using str = const std::string;
  using postfix_data = std::pair< Queue< std::string >, int >;
  using postfix_dict = AVLTree< std::string, postfix_data >;

  void addToInfixDict(infix_dict& dict, str& name, str& expr);
  void addToPostfixDict(postfix_dict& post_dict, infix_dict& in_dict, str& post_name, str& in_name, int accuracy);
  void calculate(postfix_dict& dict, str& name, std::ostream& out);
  void sumPostfix(postfix_dict& dict, str& res, str& name1, str& name2, int accuracy);
}

#endif

