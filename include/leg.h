#pragma once

#include "global.h"
#include "servo.h"
#include "debuggable.h"

class Leg: public Debuggable{
public:
  Servo i, m, o;
  float x, y, z;
  float cartesian_rotation = 0;
  float cartesian_xoffset = 0;
  float cartesian_yoffset = 0;
  bool isFlipped = false;

  void set_debug(int new_debug_level);

  Leg(int side_leg_bits):
  i(side_leg_bits | PART::INNER),
  m(side_leg_bits | PART::MIDDLE),
  o(side_leg_bits | PART::OUTER)
  {
    x = 0;
    y = 0;
    z = 0;
  };

  void set_offsets(float rot, float offx, float offy, bool flip = false);
  void convert(float& x, float& y, float& z);
  void convert_back(float& x, float& y, float& z);

  // https://www.desmos.com/calculator/pxnzvg15nf
  // idk if link will be dead after a while or not...
  // void calcAngles(float theta, float r, float height, float& innerA, float& middleA, float& outerA){
  void calcAngles(float theta, float r, float height);
  void set_cartesian(float x, float y, float height);
  void move_cartesian(float x, float y, float height);
  void test_set_r(float r, float height);
  void set_angles(float innerA, float middleA, float outerA);

  void setByIndex(int index, int angle);
};

