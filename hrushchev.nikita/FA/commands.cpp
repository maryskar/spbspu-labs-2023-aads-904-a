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

void hrushchev::addToPostfixDict(postfix_dict& post_dict,
    infix_dict& in_dict,
    variables_dict& vars,
    str& post_name,
    str& in_name,
    int accuracy)
{
  Queue< std::string > infix_queue = in_dict.at(in_name);
  Queue< std::string > postfix_queue = convertInfixToPostfix(infix_queue, vars);
  post_dict.insert(post_name, postfix_data(postfix_queue, accuracy));
}

void hrushchev::sumPostfix(postfix_dict& dict, str& res, str& name1, str& name2, int accuracy)
{
  postfix_data data1(dict.at(name1));
  postfix_data data2(dict.at(name2));
  Queue< std::string > postfix_queue1 = data1.first;
  Queue< std::string > postfix_queue2 = data2.first;
  Queue< std::string > res_queue;
  while(!postfix_queue1.isEmpty())
  {
    auto temp = postfix_queue1.get();
    postfix_queue1.pop();
    res_queue.push(temp);
  }
  while(!postfix_queue2.isEmpty())
  {
    auto temp = postfix_queue2.get();
    postfix_queue2.pop();
    res_queue.push(temp);
  }
  res_queue.push("+");
  dict.insert(res, postfix_data(res_queue, accuracy));
}

void hrushchev::subtractPostfix(postfix_dict& dict, str& res, str& name1, str& name2, int accuracy)
{
  postfix_data data1(dict.at(name1));
  postfix_data data2(dict.at(name2));
  Queue< std::string > postfix_queue1 = data1.first;
  Queue< std::string > postfix_queue2 = data2.first;
  Queue< std::string > res_queue;
  while(!postfix_queue1.isEmpty())
  {
    auto temp = postfix_queue1.get();
    postfix_queue1.pop();
    res_queue.push(temp);
  }
  while(!postfix_queue2.isEmpty())
  {
    auto temp = postfix_queue2.get();
    postfix_queue2.pop();
    res_queue.push(temp);
  }
  res_queue.push("-");
  dict.insert(res, postfix_data(res_queue, accuracy));
}

void hrushchev::multiplyPostfix(postfix_dict& dict, str& res, str& name1, str& name2, int accuracy)
{
  postfix_data data1(dict.at(name1));
  postfix_data data2(dict.at(name2));
  Queue< std::string > postfix_queue1 = data1.first;
  Queue< std::string > postfix_queue2 = data2.first;
  Queue< std::string > res_queue;
  while(!postfix_queue1.isEmpty())
  {
    auto temp = postfix_queue1.get();
    postfix_queue1.pop();
    res_queue.push(temp);
  }
  while(!postfix_queue2.isEmpty())
  {
    auto temp = postfix_queue2.get();
    postfix_queue2.pop();
    res_queue.push(temp);
  }
  res_queue.push("*");
  dict.insert(res, postfix_data(res_queue, accuracy));
}

void hrushchev::divisionPostfix(postfix_dict& dict, str& res, str& name1, str& name2, int accuracy)
{
  postfix_data data1(dict.at(name1));
  postfix_data data2(dict.at(name2));
  Queue< std::string > postfix_queue1 = data1.first;
  Queue< std::string > postfix_queue2 = data2.first;
  Queue< std::string > res_queue;
  while(!postfix_queue1.isEmpty())
  {
    auto temp = postfix_queue1.get();
    postfix_queue1.pop();
    res_queue.push(temp);
  }
  while(!postfix_queue2.isEmpty())
  {
    auto temp = postfix_queue2.get();
    postfix_queue2.pop();
    res_queue.push(temp);
  }
  res_queue.push("/");
  dict.insert(res, postfix_data(res_queue, accuracy));
}

void printQueue(hrushchev::Queue< std::string > queue, std::ostream& out)
{
  while (!queue.isEmpty())
  {
    out << queue.get();
    queue.pop();
  }
}

void hrushchev::printInfix(infix_dict& dict, std::ostream& out)
{
  for (auto it = dict.begin(); it != dict.end(); ++it)
  {
    out << it->first << " ";
    printQueue(it->second, out);
    out << "\n";
  }
}

void hrushchev::printPostfix(postfix_dict& dict, std::ostream& out)
{
  for (auto it = dict.begin(); it != dict.end(); ++it)
  {
    out << it->first << " ";
    printQueue(it->second.first, out);
    out << "\n";
  }
}

void hrushchev::help(std::ostream& out)
{
  out << "1) infix - command that takes the name and the infix expression as input. ";
  out << "It adds the infix expression to the dictionary under the given name." << "\n";

  out << "2) postfix - command that takes the name for the postfix expression, the name of the ";
  out << "infix expression from the dictionary, and an integer for precision of calculations. ";
  out << "It adds the postfix expression to the dictionary under the given name." << "\n";

  out << "3) sum_postfix - command that creates and adds a new postfix expression to the dictionary, ";
  out << "which is the sum of two given expressions. It takes the name for the result, inputs of ";
  out << "two existing expressions, and a number for precision of calculations." << "\n";

  out << "4) subtract_postfix - command that creates and adds a new postfix expression to the dictionary, ";
  out << "which is the difference of two given expressions. It takes the name for the result, inputs of ";
  out << "two existing expressions, and a number for precision of calculations." << "\n";

  out << "5) multiply_postfix - command that creates and adds a new postfix expression to the dictionary, ";
  out << "which is the product of two given expressions. It takes the name for the result, inputs of ";
  out << "two existing expressions, and a number for precision of calculations." << "\n";

  out << "6) division_postfix - command that creates and adds a new postfix expression to the dictionary, ";
  out << "which is the quotient of two given expressions. It takes the name for the result, inputs of ";
  out << "two existing expressions, and a number for precision of calculations." << "\n";

  out << "7) print_infix - command that prints the data in the dictionary with infix expressions." << "\n";

  out << "8) print_postfix - command that prints the data in the dictionary with postfix expressions." << "\n";

  out << "9) help - command that displays a list of all available commands and their descriptions." << "\n";

  out << "10) calculate - command that takes the name of a postfix expression from the dictionary and ";
  out << "outputs the result of evaluating that expression." << "\n";

  out << "11) history - command that displays a list of the last 3 executed expressions and their results." << "\n";

  out << "12) clear - command that clears the history of executed expressions." << "\n";

  out << "13) set - command that allows you to create and add a real variable to the dictionary under a given name." << "\n";

  out << "14) variable - command that outputs the value of a variable from the dictionary." << "\n";

  out << "15) variables - command that displays a list of variables." << "\n";
}

void hrushchev::calculate(postfix_dict& dict, str& name, std::ostream& out)
{
  postfix_data data = dict.at(name);
  Queue< std::string > postfix_queue = data.first;
  int accuracy = data.second;
  long double res = calculatePostfix(postfix_queue);
  out << std::setprecision(accuracy) << res << "\n";
}

void hrushchev::set(variables_dict& dict, str& name, str& value)
{
  dict.insert(name, value);
}

void hrushchev::printVariable(variables_dict& dict, str& name, std::ostream& out)
{
  try
  {
    auto var = dict.at(name);
    out << var;
  }
  catch(...)
  {
    out << "This variable dont exist\n";
  }
}

void hrushchev::printVariables(variables_dict& dict, std::ostream& out)
{
  for (auto it = dict.begin(); it != dict.end(); ++it)
  {
    out << it->first << "=" << it->second << "\n";
  }
}

