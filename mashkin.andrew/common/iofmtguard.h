#ifndef MASHKIN_ANDREW_IOFMTGUARD_H
#define MASHKIN_ANDREW_IOFMTGUARD_H
#include <ios>

namespace mashkin
{
  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();

  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}
#endif
