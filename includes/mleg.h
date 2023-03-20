#pragma once

#include "globals.h"
#include "mservo.h"
#include "debuggable.h"

#define INN_L 35.
#define MID_L 60.
#define OUT_L 80.
#define MID_L2 MID_L*MID_L
#define OUT_L2 OUT_L*OUT_L

class MLeg: public Debuggable{
public:
  MServo i, m, o;

  void set_debug(int new_debug_level);

  MLeg(SIDE side, LEG leg):
  i(side, leg, PART::INNER),
  m(side, leg, PART::MIDDLE),
  o(side, leg, PART::OUTER)
  {
    
  };

  // https://www.desmos.com/calculator/pxnzvg15nf
  // idk if link will be dead after a while or not...
  // void calcAngles(float theta, float r, float height, float& innerA, float& middleA, float& outerA){
  void calcAngles(float theta, float r, float height);
  void set_catesian(float x, float y, float height);
  void test_set_r(float r, float height);
  void set_angles(float innerA, float middleA, float outerA);
};

