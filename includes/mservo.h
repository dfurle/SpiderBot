#pragma once
#include "globals.h"
#include "debuggable.h"

class MServo: public Debuggable{
public:
  PART part;
  int id;
  float currentAngle;
  // float targetAngle;
  // float speed;

  MServo(SIDE side, LEG leg, PART part);
  float convert_angle(float angle);
  void set(float angle);
};
