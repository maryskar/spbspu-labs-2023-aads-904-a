#include "commands.hpp"
#include <string>
#include <iomanip>
#include <avltree.hpp>
#include <queue.hpp>
#include "convertstringtoinfix.hpp"
#include "convertinfixtopostfix.hpp"
#include "calcucalepostfix.hpp"

void hrushchev::addToInfixDict(infix_dict& dict, const std::string& name, const std::string& expr)
{
  Queue< std::string > infix_queue(convertStringToInfix(expr));
  dict.insert(name, infix_queue);
}

void hrushchev::addToPostfixDict(postfix_dict& post_dict, infix_dict& in_dict, str& post_name, str& in_name, int accuracy)
{
  Queue< std::string > infix_queue = in_dict.at(in_name);
  Queue< std::string > postfix_queue = convertInfixToPostfix(infix_queue);
  post_dict.insert(post_name, postfix_data(postfix_queue, accuracy));
}

void hrushchev::calculate(postfix_dict& dict, str& name, std::ostream& out)
{
  postfix_data data = dict.at(name);
  Queue< std::string > postfix_queue = data.first;
  int accuracy = data.second;
  long double res = calculatePostfix(postfix_queue);
  out << std::setprecision(accuracy) << res << "\n";
}