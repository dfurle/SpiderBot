#pragma once
#include "global.h"
#include "debuggable.h"

class MServo: public Debuggable{
public:
  PART part;
  int id;
  float currentAngle;

  int limits[2];

  // float targetAngle;
  // float speed;

  MServo(SIDE side, LEG leg, PART part);
  void setLimits(int low, int high);
  float convert_angle(float angle);
  void directDrive(float angle);
  void set(float angle);
};
