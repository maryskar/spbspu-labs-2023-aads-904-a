#include <fstream>
#include <iostream>
#include <stdexcept>
#include "convertToPostfixNotation.h"
#include "queue.h"
#include "stack.h"

int main(int argc, char** argv)
{
  if (argc != 2 && argc != 3)
  {
    std::cerr << "Incorrect arguments\n";
    return 1;
  }
  else if (argc == 3)
  {
    Stack< char > stc;
    Queue< char > que;
    std::ifstream inpFile;
    inpFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try
    {
      inpFile.open(argv[2]);
      convertToPostfixNotation(inpFile, stc, que);
    }
    catch (const std::overflow_error& ex)
    {
      std::cerr << ex.what() << "\n";
      return 1;
    }
    catch (const std::underflow_error& ex)
    {
      std::cerr << ex.what() << "\n";
      return 1;
    }
    catch (const std::exception& ex)
    {
      std::cerr << ex.what() << "\n";
      return 1;
    }
  }
  else
  {
  }
  return 0;
}
