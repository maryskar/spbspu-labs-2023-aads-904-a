#include "InfixQueue.hpp"

#include <string>

#include "InfixNode.hpp"
#include "PostfixQueue.hpp"
#include "StringSplitter.hpp"

odintsov::InfixQueue::InfixQueue(const std::string& str)
{
  StringSplitter split(str);
  while (!split.empty()) {
    std::string nodeStr;
    split >> nodeStr;
    push(InfixNode(nodeStr));
  }
}

long long odintsov::InfixQueue::solve() const
{
  return PostfixQueue(*this).solve();
}
