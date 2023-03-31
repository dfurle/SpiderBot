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

#define RAD_TO_DEG 57.295779
#define DEG_TO_RAD 0.017453
// #define M_PI 3.141592


enum class SIDE{ LEFT, RIGHT };
enum class LEG { FRONT, MIDDLE, BACK, OTHER };
enum class PART{ INNER, MIDDLE, OUTER, OTHER };


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

// Global g;