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

void hrushchev::calculate(postfix_dict& dict, str& name, std::ostream& out)
{
  postfix_data data = dict.at(name);
  Queue< std::string > postfix_queue = data.first;
  int accuracy = data.second;
  long double res = calculatePostfix(postfix_queue);
  out << std::setprecision(accuracy) << res << "\n";
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

