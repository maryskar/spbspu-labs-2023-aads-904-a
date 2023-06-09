#ifndef SPLITTER_H
#define SPLITTER_H
#include <string>
namespace timofeev
{
  class Splitter
  {
  public:
    Splitter(const std::string& str);
    const std::string& getSplit();
    bool empty() const;
  private:
    std::string str_;
    std::string split_;
  };
}
#endif
