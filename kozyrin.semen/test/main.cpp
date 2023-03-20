#include "stack.h"
#include <string>
#include <iostream>

int main() {
  std::string str;
  std::cin >> str;
  std::cout << str.pop_back();
}