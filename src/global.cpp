#include "global.h"

Global::Global(){

}



template<class T>
const T& Global::constrain(const T& x, const T& a, const T& b) {
  if(x < a) {
    return a;
  }
  else if(b < x) {
    return b;
  }
  else
    return x;
}

long Global::map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
