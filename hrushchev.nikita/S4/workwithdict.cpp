#include "workwithdict.hpp"
#include <printerror.hpp>
#include "commands.hpp"

hrushchev::Commands::Commands()
{
  dict1_.insert("print", printDict);
  dict2_.insert("complement", complementDict);
  dict2_.insert("intersect", intersectDict);
  dict2_.insert("union", unionDict);
}

void hrushchev::Commands::runCommand(std::istream& in, std::ostream& out, main_dict& dict_of_dict)
{
  std::string command = "";
  while (in >> command)
  {
    std::string res_dict_name = "";
    in >> res_dict_name;
    try
    {
      auto func = dict1_.at(command);
      func(res_dict_name, dict_of_dict, out);
      out << "\n";
      continue;
    }
    catch (...)
    {
    }

    std::string first_dict_name = "";
    std::string second_dict_name = "";
    in >> first_dict_name >> second_dict_name;
    try
    {
      auto func = dict2_.at(command);
      func(res_dict_name, first_dict_name, second_dict_name, dict_of_dict);
    }
    catch (const std::out_of_range& e)
    {
      printError(out);
    }
  }
}
