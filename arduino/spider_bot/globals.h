#ifndef GLOBALS_H
#define GLOBALS_H
#include <Adafruit_PWMServoDriver.h>

// --- TODO: figure out what is best to use with many servos. ---
#define LMIN 80
#define LMAX 460
// #define LMIN 102
// #define LMAX 512
// int LMIN = 500./20000 * 4096;
// int LMID = 1500./20000 * 4096;
// int LMAX = 2500./20000 * 4096;

int hard_limits[4][2] = {
  {0, 90}, // INNER
  {45, 180}, // MIDDLE
  {0, 120}, // OUTER
  {0,0} // ignore
};

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

enum class SIDE{ LEFT, RIGHT };
enum class LEG { FRONT, MIDDLE, BACK, OTHER };
enum class PART{ INNER, MIDDLE, OUTER, OTHER };

// ---- testing stuffs ----




#endif