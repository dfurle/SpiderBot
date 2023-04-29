#pragma once
#include "leg.h"
#include "global.h"
#include <vector>

class Body{
public:

  std::vector<Leg*> legs;

  Body();

  // WARNING, CAUSES MEMORY LEAK WHEN RAN MULTIPLE TIMES!!!
  void initialize();

  Leg* getLeg(int bits);

  // only input single bit, get single servo
  Servo* getServo(int bits);

  template<typename Func>
  void runForServos(Func f, int bits);

  template<typename Func>
  void runForLegs(Func f, int bits);

  void setLimits(int min, int max, int bits);

  // can input multiple bits for servo
  void setServos(int angle, int bits);

  void setXYZ(int x, int y, int z, int bits);
};
