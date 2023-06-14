#ifndef INPUTINFIXQUEUE_H
#define INPUTINFIXQUEUE_H

namespace potapova
{
  std::istream& inputInfixQueue(potapova::Queue< potapova::ArithmExpMember >& dest, std::istream& in = std::cin);
  bool isOperation(char& sym);
}

#endif
