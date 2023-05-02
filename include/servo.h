#pragma once
#include "global.h"
#include "debuggable.h"

class Servo: public Debuggable{
public:
  int part;
  int bits;
  int id;
  float currentAngle;
  int a, ad;
  float scaling = 1;

  int limits[2];

  // float targetAngle;
  // float speed;

  Servo(int side_leg_servo_bits);
  void setLimits(int low, int high);
  float convert_angle(float angle);
  void directDrive(float angle);
  void set(float angle);
};
