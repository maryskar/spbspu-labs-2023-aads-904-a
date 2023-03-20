#include "notation.h"

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

}