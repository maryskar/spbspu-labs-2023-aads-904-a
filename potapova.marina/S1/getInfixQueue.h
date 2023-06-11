#ifndef GETINFIXQUEUE_H
#define GETINFIXQUEUE_H

namespace potapova
{
  bool getInfixQueue(potapova::Queue< potapova::ArithmExpMember >& dest, std::istream& in = std::cin);
  bool isOperation(std::string& sym);
}

#endif
