#include "workwithdict.hpp"
#include <string>
#include <iostream>
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

void hrushchev::Commands::runCommand(std::istream& in, std::ostream& out)
{
  namespace hrn = hrushchev;
  hrn::AVLTree< std::string, hrn::Queue< std::string > > dict_with_infix;
  hrn::AVLTree< std::string, std::pair< hrn::Queue< std::string >, int > > dict_with_postfix;
  hrn::AVLTree< std::string, std::string > dict_with_vars;
  while(in)
  {
    std::string command;
    in >> command;

    try
    {
      auto func = dict1_.at(command);
      std::string name;
      std::string expr;
      in >> name >> expr;
      func(dict_with_infix, name, expr);
    }
    catch (...)
    {
    }

    try
    {
      auto func = dict2_.at(command);
      std::string post_name;
      std::string in_name;
      int accuracy = 0;
      in >> post_name >> in_name >> accuracy;
      func(dict_with_postfix, dict_with_infix, dict_with_vars, post_name, in_name, accuracy);
    }
    catch (...)
    {
    }

    try
    {
      auto func = dict3_.at(command);
      std::string res_name;
      std::string first_name;
      std::string second_name;
      int accuracy = 0;
      in >> res_name >> first_name >> second_name >> accuracy;
      func(dict_with_postfix, res_name, first_name, second_name, accuracy);
    }
    catch (...)
    {
    }

    try
    {
      auto func = dict4_.at(command);
      func(dict_with_infix, out);
    }
    catch (...)
    {
    }

    try
    {
      auto func = dict5_.at(command);
      func(dict_with_postfix, out);
    }
    catch (...)
    {
    }

    try
    {
      auto func = dict6_.at(command);
      func(out);
    }
    catch (...)
    {
    }

    try
    {
      auto func = dict7_.at(command);
      std::string name;
      in >> name;
      func(dict_with_postfix, name, out);
    }
    catch (...)
    {
    }

    try
    {
      auto func = dict8_.at(command);
      std::string name;
      std::string value;
      in >> name >> value;
      func(dict_with_vars, name, value);
    }
    catch (...)
    {
    }

    try
    {
      auto func = dict9_.at(command);
      std::string name;
      in >> name;
      func(dict_with_vars, name, out);
    }
    catch (...)
    {
    }

    try
    {
      auto func = dict10_.at(command);
      func(dict_with_vars, out);
    }
    catch (...)
    {
    }
  }
}

