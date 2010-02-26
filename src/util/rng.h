// RNG.h

#ifndef _RNG_H_
#define _RNG_H_ 1

class RNG
{
public:
   RNG(unsigned long long _seed = 7564231ULL) 
   {
      seed      = _seed;
      mult      = 62089911ULL;
      llong_max = 4294967295ULL;
      double_max = 4294967295.0f;
   }
   double operator()();               

   unsigned long long seed;
   unsigned long long mult;
   unsigned long long llong_max;
   double double_max;
};

inline double RNG::operator()()
{
   seed = mult * seed;
   return double(seed % llong_max) / double_max;  
}
#endif // _RNG_H_
