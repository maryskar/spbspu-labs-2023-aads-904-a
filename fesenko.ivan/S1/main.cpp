#include <iostream>
#include <fstream>
#include "stack.h"
#include "queue.h"
#include "stringToInfixQueue.h"
#include "infixQueueToPostfixQueue.h"
#include "calculateInPostfixQueue.h"

int main(/*int argc, char *argv[]*/)
{
  /*if (argc != 1 && argc != 2) {
    std::cerr << "Invalid number of arguments\n";
    return 1;
  }
  std::ifstream input;
  if (argc == 2) {
    input.open(argv[1]);
  }
  std::istream &in = (argc == 2) ? input : std::cin;*/
  std::string expression = "";
  long long result = 0;
  fesenko::Stack< long long > results;
  while (std::cin) {
    std::getline(std::cin, expression);
    if (expression.empty()) {
      continue;
    }
    try {
      fesenko::Queue< std::string > infixQueue = fesenko::stringToInfixQueue(expression);
      fesenko::Queue< std::string > postfixQueue = fesenko::infixQueueToPostfixQueue(infixQueue);
      result = fesenko::calculateInPostfixQueue(postfixQueue);
      results.push(result);
    } catch (const std::exception &e) {
      std::cerr << e.what() << "\n";
      return 2;
    }
  }
  while (!results.isEmpty()) {
    result = results.top();
    results.pop();
    if (results.isEmpty()) {
      std::cout << result << "\n";
    } else {
      std::cout << result << " ";
    }
  }
}
