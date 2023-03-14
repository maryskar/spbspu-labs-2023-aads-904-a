#ifndef DATA_TYPE
#define DATA_TYPE

struct calc_t
{
  operator long long() const;
  operator char() const;
  calc_t operator=(long long num);
  calc_t operator=(char sign);
  bool operator==(long long num);
  bool operator==(char sign);
  bool operator!=(long long num);
  bool operator!=(char sign);
  union
  {
    long long num;
    char sign;
  } calc;
  bool isgigit;
};

#endif
