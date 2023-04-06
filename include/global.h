#pragma once

#include <PCA/PCA9685.h>
#include <string.h>
#include <cmath>
#include <unistd.h>

// --- TODO: figure out what is best to use with many servos. ---
#define LMIN 0.5f  // 80
#define LMAX 2.5f // 460
// #define LMIN 102
// #define LMAX 512
// int LMIN = 500./20000 * 4096;
// int LMID = 1500./20000 * 4096;
// int LMAX = 2500./20000 * 4096;


// #define INN_L 35.
// #define MID_L 60.
// #define OUT_L 80.
#define INN_L 45.
#define MID_L 104.
#define OUT_L 208.
#define MID_L2 MID_L*MID_L
#define OUT_L2 OUT_L*OUT_L

#define RAD_TO_DEG 57.295779
#define DEG_TO_RAD 0.017453
// #define M_PI 3.141592


class SIDE{ 
public:
  static const unsigned int LEFT = 1;
  static const unsigned int RIGHT = 1<<1;
  static const unsigned int ALL = LEFT | RIGHT;
  static const unsigned int MIN=0;
};
class LEG {
public:
  static const unsigned int FRONT = 1<<2;
  static const unsigned int MIDDLE=1<<3;
  static const unsigned int BACK=1<<4;
  static const unsigned int ALL = FRONT | MIDDLE | BACK;
  static const unsigned int MIN=2;
};
class PART{
public:
  static const unsigned int INNER = 1<<5;
  static const unsigned int MIDDLE=1<<6;
  static const unsigned int OUTER=1<<7;
  static const unsigned int ALL = INNER | MIDDLE | OUTER;
  static const unsigned int MIN=5;
};



class Global{
public:
  Global();

  const int hard_limits[4][2] = {
    {0, 90}, // INNER
    {45, 172}, // MIDDLE
    {0, 115}, // OUTER
    {0,0} // ignore
  };

  PiPCA9685::PCA9685 left{"/dev/i2c-1",0x40};
  PiPCA9685::PCA9685 right{"/dev/i2c-1",0x41};


  void print_bin(std::string title, short val);

  int findSetBit(std::uint32_t bits){
    if (!(bits && !(bits & (bits-1))))
      return 0;
    return log2(bits) + 1;
  }

  int strip(int bits, int all){
    int v = bits & all;
    return v;
  }


  template<class T>
  const T& constrain(const T& x, const T& a, const T& b) {
    if(x < a) {
      return a;
    }
    else if(b < x) {
      return b;
    }
    else
      return x;
  }

  template<class T>
  const T map(const T& x, const T& in_min, const T& in_max, const T& out_min, const T& out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
};

extern Global g;