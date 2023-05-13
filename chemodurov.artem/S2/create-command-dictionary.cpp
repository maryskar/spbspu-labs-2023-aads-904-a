#include "create-command-dictionary.hpp"

namespace chemodurov
{
  void printCommand(std::istream & in, std::ostream & out, Dictionary< std::string, dic_t > & data)
  {
    std::string name;
    in >> name;
    Dictionary< std::string, dic_t >::mapped_type dic = data.at(name);
    if (!in)
    {
      throw std::invalid_argument("Invalid command");
    }
    if (dic.empty())
    {
      out << "<EMPTY>\n";
      return;
    }
    print(out, {name, dic});
    out << '\n';
  }

  template< typename P >
  void complementOrIntersect(std::istream & in, std::ostream &, Dictionary< std::string, dic_t > & data, P p)
  {
    std::string name_res;
    in >> name_res;
    dic_t res;
    std::string name_fst;
    in >> name_fst;
    std::string name_snd;
    in >> name_snd;
    Dictionary< std::string, dic_t >::iterator it_fst = data.find(name_fst);
    Dictionary< std::string, dic_t >::iterator it_snd = data.find(name_snd);
    if (!in || ++it_fst == data.end() || ++it_snd == data.end())
    {
      throw std::invalid_argument("Invalid command");
    }
    res = it_fst->second;
    for (auto i = res.begin(); i != res.end(); ++i)
    {
      if (p(it_snd->second.find(i->first), it_snd->second.last()))
      {
        res.erase(i->first);
        i = res.before_begin();
      }
    }
    data.insert({name_res, res});
  }

  void complementCommand(std::istream & in, std::ostream & out, Dictionary< std::string, dic_t > & data)
  {
    complementOrIntersect(in, out, data, std::not_equal_to< >{});
  }

  void intersectCommand(std::istream & in, std::ostream & out, Dictionary< std::string, dic_t > & data)
  {
    complementOrIntersect(in, out, data, std::equal_to< >{});
  }

  void unionCommand(std::istream & in, std::ostream &, Dictionary< std::string, dic_t > & data)
  {
    std::string name_res;
    in >> name_res;
    dic_t res;
    std::string name_fst;
    in >> name_fst;
    std::string name_snd;
    in >> name_snd;
    Dictionary< std::string, dic_t >::iterator it_fst = data.find(name_fst);
    Dictionary< std::string, dic_t >::iterator it_snd = data.find(name_snd);
    if (!in || ++it_fst == data.end() || ++it_snd == data.end())
    {
      throw std::invalid_argument("Invalid command");
    }
    res = it_snd->second;
    res.insert(it_fst->second.begin(), it_fst->second.end());
    data.insert({name_res, res});
  }

  Dictionary< std::string, command_t > createCommandDictionary()
  {
    Dictionary< std::string, command_t > res;
    res.insert({"print", printCommand});
    res.insert({"complement", complementCommand});
    res.insert({"intersect", intersectCommand});
    res.insert({"union", unionCommand});
    return res;
  }
}
