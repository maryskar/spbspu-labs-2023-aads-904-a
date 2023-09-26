#ifndef OUTERRORMSG_HPP
#define OUTERRORMSG_HPP

#include <iosfwd>

namespace odintsov {
  std::ostream& outInvalidCommandMsg(std::ostream& out);
  std::ostream& outEmptyContainerMsg(std::ostream& out);
}

#endif
