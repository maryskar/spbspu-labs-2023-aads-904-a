#ifndef S4_IOREALIZATION_H
#define S4_IOREALIZATION_H
#include <ios>
#include "AVL.h"

namespace mashkin
{
  using dictionary = AVL< int, std::string >;
  using dictionaries = AVL< std::string, dictionary >;

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

  std::istream& operator>>(std::istream& inp, dictionary& dict);
  std::istream& operator>>(std::istream& inp, dictionaries& dicts);
  std::ostream& operator<<(std::ostream& out, const dictionary& dicts);
}
#endif
