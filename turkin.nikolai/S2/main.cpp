#include <iostream>
#include <fstream>
#include "forward-list.hpp"

int main(int argc, char * argv[])
{
  if (argc == 1)
  {
    std::cerr << "no file\n";
    return 1;
  }

  std::ifstream file;
  file.open(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "cannot open file\n";
    return 1;
  }
  std::cout << "HI!\n";

  ForwardList< int > fl;
  fl.push_front(1);
  fl.push_front(2);
  fl.push_front(3);
  fl.push_front(4);
  std::cout << "front: " << fl.front() << "\n";
  std::cout << "front: " << *fl.begin() << "\n";
  std::cout << "front: " << *fl.cbegin() << "\n";
  std::cout << "back: " << *fl.end() << "\n";
  std::cout << "back: " << *fl.cend() << "\n";
  return 0;
}
