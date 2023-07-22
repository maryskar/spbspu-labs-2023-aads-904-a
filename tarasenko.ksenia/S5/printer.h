#ifndef PRINTER_H
#define PRINTER_H
namespace tarasenko
{
  class Printer
  {
  public:
   Printer(std::ostream& out):
     wasCalled_(false),
     out_(out)
   {}
   void operator()(const std::pair< long long, std::string >& key_value)
   {
     if (wasCalled_)
     {
       out_ << " " << key_value.second;
       return;
     }
     out_ << key_value.second;
     wasCalled_ = true;
   }

  private:
   bool wasCalled_;
   std::ostream& out_;
  };
}
#endif
