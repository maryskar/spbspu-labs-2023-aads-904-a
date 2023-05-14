#include "create-command-dictionary.hpp"

namespace chemodurov
{
  void printCommand(std::istream & in, std::ostream & out, const Dictionary< std::string, dic_t > & data)
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
  void complementOrIntersect(std::istream & in, Dictionary< std::string, dic_t > & data, P p)
  {
    std::string name_res;
    in >> name_res;
    dic_t res;
    std::string name_fst;
    in >> name_fst;
    std::string name_snd;
    in >> name_snd;
    Dictionary< std::string, dic_t >::mapped_type fst_dic = data.at(name_fst);
    Dictionary< std::string, dic_t >::mapped_type snd_dic = data.at(name_snd);
    if (!in)
    {
      throw std::invalid_argument("Invalid command");
    }
    res = fst_dic;
    for (auto i = res.begin(); i != res.end(); ++i)
    {
      if (p(snd_dic.find(i->first), snd_dic.last()))
      {
        res.erase(i->first);
        i = res.before_begin();
      }
    }
    data.insert({name_res, res});
  }

  void complementCommand(std::istream & in, Dictionary< std::string, dic_t > & data)
  {
    complementOrIntersect(in, data, std::not_equal_to< >{});
  }

  void intersectCommand(std::istream & in, Dictionary< std::string, dic_t > & data)
  {
    complementOrIntersect(in, data, std::equal_to< >{});
  }

  void unionCommand(std::istream & in, Dictionary< std::string, dic_t > & data)
  {
    std::string name_res;
    in >> name_res;
    dic_t res;
    std::string name_fst;
    in >> name_fst;
    std::string name_snd;
    in >> name_snd;
    Dictionary< std::string, dic_t >::mapped_type fst_dic = data.at(name_fst);
    Dictionary< std::string, dic_t >::mapped_type snd_dic = data.at(name_snd);
    if (!in)
    {
      throw std::invalid_argument("Invalid command");
    }
    res = snd_dic;
    res.insert(fst_dic.begin(), fst_dic.end());
    data.insert({name_res, res});
  }

  std::pair< Dictionary< std::string, union_t >, Dictionary< std::string, print_t > > createCommandDictionary()
  {
    Dictionary< std::string, union_t > unions;
    Dictionary< std::string, print_t > print;
    print.insert({"print", printCommand});
    unions.insert({"complement", complementCommand});
    unions.insert({"intersect", intersectCommand});
    unions.insert({"union", unionCommand});
    return {unions, print};
  }
}
