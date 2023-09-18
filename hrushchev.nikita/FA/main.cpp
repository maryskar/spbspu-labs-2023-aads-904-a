#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <avltree.hpp>
#include "convertstringtoinfix.hpp"
#include "convertinfixtopostfix.hpp"
#include "calcucalepostfix.hpp"
#include "commands.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "workwithdict.hpp"

int main()
{
  namespace hrn = hrushchev;
  hrn::Commands cmd;

  cmd.runCommand(std::cin);
}
