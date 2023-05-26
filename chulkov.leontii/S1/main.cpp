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
    Stack< long long > result;
    while (std::getline(in, str)) {
      if (!in) {
        break;
      }
      if (str.empty()) {
        continue;
      }
      Queue< std::string > post = infixToPostfix(str);
      result.push(calculatePostfix(post));
      if (!result.empty()) {
        std::cout << result.drop() << '\n';
      }
    }

  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
