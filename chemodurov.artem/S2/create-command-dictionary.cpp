#include "create-command-dictionary.hpp"

namespace chemodurov
{
  void print(std::istream & in, std::ostream & out, Dictionary< std::string, dic_t > & data)
  {
    std::string name = "";
    in >> name;
    Dictionary< std::string, dic_t >::iterator it = data.find(name);
    if (!in || it == data.end())
    {
      throw std::invalid_argument("Invalid command");
    }
    if ((++it)->second.empty())
    {
      out << "<EMPTY>\n";
      return;
    }
    out << *(it) << '\n';
  }

  template< typename P >
  void complementOrIntersect(std::istream & in, std::ostream &, Dictionary< std::string, dic_t > & data, P p)
  {
    std::string name_res = "";
    in >> name_res;
    dic_t res;
    std::string name_fst = "";
    in >> name_fst;
    std::string name_snd = "";
    in >> name_snd;
    Dictionary< std::string, dic_t >::iterator it_fst = data.find(name_fst);
    Dictionary< std::string, dic_t >::iterator it_snd = data.find(name_snd);
    if (!in || it_fst == data.end() || it_snd == data.end())
    {
      throw std::invalid_argument("Invalid command");
    }
    ++it_snd;
    res = (++it_fst)->second;
    for (auto i = res.begin(); i != res.end(); ++i)
    {
      if (p(it_snd->second.find(i->first), it_snd->second.end()))
      {
        res.erase(i->first);
      }
    }
    data.insert({name_res, res});
  }

  void complement(std::istream & in, std::ostream & out, Dictionary< std::string, dic_t > & data)
  {
    complementOrIntersect(in, out, data, std::not_equal_to< >{});
  }

  void intersect(std::istream & in, std::ostream & out, Dictionary< std::string, dic_t > & data)
  {
    complementOrIntersect(in, out, data, std::equal_to< >{});
  }
}
