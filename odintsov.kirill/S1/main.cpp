#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "MathSolver.hpp"
#include "Stack.hpp"
#include "StringSplitter.hpp"

int main(int argc, char* argv[])
{
  std::istream* in = &std::cin;
  std::ifstream inFile;
  if (argc == 2) {
    inFile.open(argv[1]);
    if (!inFile.is_open()) {
      std::cerr << "Can't open file\n";
      return 1;
    }
    in = &inFile;
  } else if (argc != 1) {
    std::cerr << "Incorrect amount of arguments\n";
    return 1;
  }

  odintsov::Stack< long long > results;
  try {
    while (in->good()) {
      std::string exprStr;
      std::getline(*in, exprStr);
      if (!in) {
        throw std::runtime_error("Input error");
      }
      if (exprStr.empty()) {
        continue;
      }
      odintsov::StringSplitter splitter(exprStr);
      odintsov::MathSolver addToSolution;
      while (!splitter.empty()) {
        std::string nodeStr;
        splitter >> nodeStr;
        addToSolution(nodeStr);
      }
      results.push(addToSolution.getResult());
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  if (results.empty()) {
    std::cout << '\n';
    return 0;
  }
  std::cout << results.tail();
  results.pop();
  while (!results.empty()) {
    std::cout << ' ' << results.tail();
    results.pop();
  }
  std::cout << '\n';
}
