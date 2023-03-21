#include "computestr.h"

int main(int argc, char** argv)
{
  std::ifstream fin;
  if (argc == 2) {
    fin.open(argv[1]);
    if (!fin.is_open()) {
      std::cerr << "Error: input file could not be opened";
    }
  } else if (argc != 1) {
    std::cerr << "Error: incorrect arguments";
    return 1;
  }
  std::istream& input = argc == 2 ? fin : std::cin;

  Stack< int > stack = Stack< int >();
  std::string str = "";

  while (!input.eof()) {
    getline(input, str);
    if (str.empty()) {
      continue;
    }
    try {
      stack.push(computeString(str));
    }
    catch (const std::exception& err) {
      std::cerr << "Error: " << err.what();
      return 2;
    }
  }
  while(!stack.isEmpty()) {
    std::cout << stack.drop() << ' ';
  }
}
