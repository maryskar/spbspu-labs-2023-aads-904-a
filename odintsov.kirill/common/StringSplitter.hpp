#ifndef STRINGSPLITTER_HPP
#define STRINGSPLITTER_HPP

#include <string>

namespace odintsov {
  class StringSplitter {
   public:
    explicit StringSplitter(const std::string& str);

    StringSplitter& operator>>(std::string& ostr);

    bool empty() const;

   private:
    std::string str_;
  };
}

#endif
