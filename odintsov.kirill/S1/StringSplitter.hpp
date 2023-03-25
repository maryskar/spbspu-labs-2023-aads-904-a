#ifndef STRINGSPLITTER_HPP
#define STRINGSPLITTER_HPP

#include <string>

namespace odintsov {
  class StringSplitter {
   public:
    explicit StringSplitter(const std::string& str);

    StringSplitter& operator>>(std::string& ostr);

   private:
    std::string str_;
  };
}

#endif
