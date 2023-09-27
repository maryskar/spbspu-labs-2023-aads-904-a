#include "Commands.h"
#include "commandSet.h"
namespace timofeev
{
  void Print(std::istream& in, dictOfDicts& dict, std::ostream& out)
  {
    try
    {
      std::string dictName;
      in >> dictName;
      if (dict.contains(dictName))
      {
        dictionary dict_t = dict.at(dictName);
        if (!dict_t.empty())
        {
          out << dictName;
          for (auto & i : dict_t)
          {
            out << " " << i.first << " " << i.second;
          }
        }
        else
        {
          out << "<EMPTY>" << '\n';
          return;
        }
      }
      else
      {
        return;
      }
    }
    catch (...)
    {
      throw;
    }
  }
}
