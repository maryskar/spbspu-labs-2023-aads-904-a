#ifndef S4_IOREALIZATION_H
#define S4_IOREALIZATION_H
#include <ios>
#include "AVL.h"
#include "queue.h"
#include "stack.h"
#include "../S5/structsForTraverse.h"

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
  std::ostream& operator<<(std::ostream& out, const Queue< std::string >& que);
  std::ostream& operator<<(std::ostream& out, const Stack< std::string >& stack);
  std::ostream& operator<<(std::ostream& out, const QueueForTraverse& queueForTraverse);
  std::ostream& operator<<(std::ostream& out, const StackForTraverse& stackForTraverse);
}
#endif
