#include <fstream>
#include <iostream>
#include <string>

#include "infixexpressionconversions.h"
#include "postfixvaluecalculation.h"
#include "queue.h"
#include "stack.h"

int main(int argc, char* argv[]) {
  if (argc > 2) {
    std::cerr << "Error argv\n";
    return 1;
  }
  std::ifstream input;
  if (argc == 2) {
    input.open(argv[1]);
    if (!input.is_open()) {
      std::cerr << "Error, file is not open\n";
      return 1;
    }
  }
  std::istream& in = (argc == 2) ? input : std::cin;
  std::string str;
  try {
    chulkov::Stack< long long > result;
    while (std::getline(in, str)) {
      if (str.empty()) {
        continue;
      }
      chulkov::Queue< std::string > post = chulkov::infixToPostfix(str);
      result.push(calculatePostfix(post));
    }
    while (!result.empty()) {
      std::cout << result.drop();
      if (!result.empty()) {
        std::cout << " ";
      }
    }
    std::cout << '\n';
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
