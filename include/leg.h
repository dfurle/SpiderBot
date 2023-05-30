#pragma once

#include "global.h"
#include "servo.h"
#include "debuggable.h"
#include "vec.h"

class Leg: public Debuggable{
public:
  Servo i, m, o;
  Vec3f pos, offset;
  float cartesian_rotation = 0;
  bool isFlipped = false;

  void set_debug(int new_debug_level);

  Leg(int side_leg_bits):
  i(side_leg_bits | PART::INNER),
  m(side_leg_bits | PART::MIDDLE),
  o(side_leg_bits | PART::OUTER)
  {

  };

  void set_offsets(float rot, float offx, float offy, bool flip = false);
  void convert(Vec3f& pos);
  void convert_back(Vec3f& pos);

  // https://www.desmos.com/calculator/pxnzvg15nf
  // idk if link will be dead after a while or not...
  // void calcAngles(float theta, float r, float height, float& innerA, float& middleA, float& outerA){
  void calcAngles(float theta, float r, float height);
  void set_cartesian(Vec3f pos);
  void move_cartesian(Vec3f pos);
  void move_cartesian_speed(Vec3f pos, float speed);
  void test_set_r(float r, float height);
  void set_angles(float innerA, float middleA, float outerA);

  void setByIndex(int index, int angle);
};

