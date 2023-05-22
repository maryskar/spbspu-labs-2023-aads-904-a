#include "create-command-dictionary.hpp"

namespace chemodurov
{
  std::ostream & outEmpty(std::ostream & out)
  {
    return out << "<EMPTY>";
  }

  std::ostream & outInvalidCommand(std::ostream & out)
  {
    return out << "<INVALID COMMAND>";
  }

  void printCommand(std::istream & in, std::ostream & out, const Map< std::string, dic_t > & data)
  {
    std::string name;
    in >> name;
    Map< std::string, dic_t >::mapped_type dic = data.at(name);
    if (!in)
    {
      throw std::invalid_argument("Invalid command");
    }
    if (dic.empty())
    {
      outEmpty(out);
      out << '\n';
      return;
    }
    print(out, {name, dic});
    out << '\n';
  }

  template< typename P >
  void complementOrIntersect(std::istream & in, Map< std::string, dic_t > & data, P p)
  {
    std::string name_res;
    in >> name_res;
    dic_t res;
    std::string name_fst;
    in >> name_fst;
    std::string name_snd;
    in >> name_snd;
    Map< std::string, dic_t >::mapped_type fst_dic = data.at(name_fst);
    Map< std::string, dic_t >::mapped_type snd_dic = data.at(name_snd);
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

  void complementCommand(std::istream & in, Map< std::string, dic_t > & data)
  {
    complementOrIntersect(in, data, std::not_equal_to< >{});
  }

  void intersectCommand(std::istream & in, Map< std::string, dic_t > & data)
  {
    complementOrIntersect(in, data, std::equal_to< >{});
  }

  void unionCommand(std::istream & in, Map< std::string, dic_t > & data)
  {
    std::string name_res;
    in >> name_res;
    dic_t res;
    std::string name_fst;
    in >> name_fst;
    std::string name_snd;
    in >> name_snd;
    Map< std::string, dic_t >::mapped_type fst_dic = data.at(name_fst);
    Map< std::string, dic_t >::mapped_type snd_dic = data.at(name_snd);
    if (!in)
    {
      throw std::invalid_argument("Invalid command");
    }
    res = snd_dic;
    res.insert(fst_dic.begin(), fst_dic.end());
    data.insert({name_res, res});
  }

  std::pair< Map< std::string, union_t >, Map< std::string, print_t > > createCommandDictionary()
  {
    Map< std::string, union_t > unions;
    Map< std::string, print_t > print;
    print.insert({"print", printCommand});
    unions.insert({"complement", complementCommand});
    unions.insert({"intersect", intersectCommand});
    unions.insert({"union", unionCommand});
    return {unions, print};
  }
}
