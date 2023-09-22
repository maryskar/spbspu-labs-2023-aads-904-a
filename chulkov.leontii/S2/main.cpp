#include <fstream>
#include <iostream>
#include <string>
#include "Commands.h"
#include "getDicts.h"

std::ostream& chulkov::printInvalidCommand(std::ostream& out)
{
  return out << "<INVALID COMMAND>\n";
};

int main(int argc, char* argv[])
{
  if (argc == 1) {
    std::cerr << "Can't read file\n" << std::endl;
    return 1;
  }
  std::ifstream in_stream(argv[1]);
  if (!in_stream.good()) {
    std::cerr << "Unable to read the file\n" << std::endl;
    return 1;
  }
  try {
    auto data = chulkov::getDicts(in_stream);
    in_stream.close();
    std::istream& in = std::cin;

    while (!in.eof()) {
      try {
        chulkov::FrdList< std::string > words = chulkov::getWords(in, '\n');
        if (words.isEmpty()) {
          continue;
        }
        int wordCount = 0;
        for (chulkov::ForwardConstIter< std::string > it = words.cbegin(); it != words.cend(); ++it) {
          ++wordCount;
        }
        if (wordCount < 2) {
          throw std::invalid_argument("You need more args!\n");
        }
        chulkov::ForwardConstIter< std::string > wordsIterator = words.cbegin();
        std::string command = *(wordsIterator++);
        std::string name = *(wordsIterator++);

        if (command == "print") {
          chulkov::print(std::cout, name, data);
          continue;
        }

        if (wordCount < 4) {
          throw std::invalid_argument("You need less args!\n");
        }

        std::string lhs = *(wordsIterator++);
        std::string rhs = *wordsIterator;

        if (command == "complement") {
          data.push(name, chulkov::complement(lhs, rhs, data));
        } else if (command == "intersect") {
          data.push(name, chulkov::intersect(lhs, rhs, data));
        } else if (command == "union") {
          data.push(name, chulkov::unite(lhs, rhs, data));
        } else {
          throw std::invalid_argument("Unknown command\n");
        }
      } catch (const std::invalid_argument&) {
        chulkov::printInvalidCommand(std::cout);
      }
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 2;
  }
  return 0;
}
