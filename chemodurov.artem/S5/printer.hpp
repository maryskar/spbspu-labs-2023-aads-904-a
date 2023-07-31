#ifndef S5_PRINTER_HPP
#define S5_PRINTER_HPP
#include <iosfwd>
#include <utility>

namespace chemodurov
{
  class Printer
  {
   public:
    explicit Printer(std::ostream & out);
    void operator()(const std::pair< const long, std::string > & pair);
   private:
    std::ostream & out_;
    bool was_printed_;
  };
}

#endif
