#pragma once

#include <PCA/PCA9685.h>
// #include <string.h>
#include <cmath>
#include <unistd.h>
#include <map>
#include <iostream>
#include <string>

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
#define MID_L 115.
#define OUT_L 230.
#define MID_L2 MID_L*MID_L
#define OUT_L2 OUT_L*OUT_L

#define RAD_TO_DEG 57.295779
#define DEG_TO_RAD 0.017453
// #define M_PI 3.141592


#define id_FR 0
#define id_MR 1
#define id_RR 2

#define id_FL 3
#define id_ML 4
#define id_RL 5


class LEG {
public:
  static const unsigned int MIN = 0;
  static const unsigned int FRONT_RIGHT  = 1<<0;
  static const unsigned int MIDDLE_RIGHT = 1<<1;
  static const unsigned int REAR_RIGHT   = 1<<2;
  static const unsigned int FRONT_LEFT  = 1<<3;
  static const unsigned int MIDDLE_LEFT = 1<<4;
  static const unsigned int REAR_LEFT   = 1<<5;

  static const unsigned int FL = FRONT_LEFT;
  static const unsigned int ML = MIDDLE_LEFT;
  static const unsigned int RL = REAR_LEFT;
  static const unsigned int FR = FRONT_RIGHT;
  static const unsigned int MR = MIDDLE_RIGHT;
  static const unsigned int RR = REAR_RIGHT;
  static const unsigned int LEFT = FL | ML | RL;
  static const unsigned int RIGHT = FR | MR | RR;
  static const unsigned int ALL = LEFT | RIGHT;
};
class PART{
public:
  static const unsigned int MIN = 6;
  static const unsigned int INNER  = 1<<6;
  static const unsigned int MIDDLE = 1<<7;
  static const unsigned int OUTER  = 1<<8;
  static const unsigned int ALL = INNER | MIDDLE | OUTER;
};
class COMMON{
public:
  static const unsigned int TRI_RIGHT = LEG::FR | LEG::RR | LEG::ML;
  static const unsigned int TRI_LEFT  = LEG::FL | LEG::RL | LEG::MR;
};



class Global{
public:
  Global();

  PiPCA9685::PCA9685 right{"/dev/i2c-1",0x40};
  PiPCA9685::PCA9685 left{"/dev/i2c-1",0x41};


  void print_bin(std::string title, short val);

  int findSetBit(int bits){
    if (!(bits && !(bits & (bits-1))))
      return 0;
    return log2(bits) + 1;
  }

  int strip(int bits, int all){
    int v = bits & all;
    return v;
  }

  int toBits(std::string str, int current_bits, std::map<std::string, int>& map);

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